# Lean4生成CコードをRISC Zero zkVMで実行する際の課題

## 概要

Lean4が生成するCコードをRISC Zero zkVMのゲストプログラムで実行するフィジビリティを検証した結果、以下の課題が明らかになった。

---

## 課題一覧

### 課題1: Leanランタイム依存

**問題:**
生成されるCコードは`lean/lean.h`ヘッダとLeanランタイムライブラリに依存する。

```c
#include <lean/lean.h>  // RISC Zero環境に存在しない
```

**影響:**
- RISC Zero guestは`no_std` + `-ffreestanding -nostdlib`でビルドされる
- Leanランタイムライブラリ（libLean）はRISC-V向けにビルドされていない
- ランタイム初期化関数`lean_initialize_runtime_module()`が呼び出せない

---

### 課題2: 参照カウントによるメモリ管理

**問題:**
Lean4は`lean_object*`型でヒープオブジェクトを管理し、参照カウントで寿命を追跡する。

```c
lean_inc(x_1);   // 参照カウント増加
lean_dec(x_5);   // 参照カウント減少、0になったら解放
```

**影響:**
- `lean_inc`/`lean_dec`はLeanランタイムの関数
- アトミック操作を含む可能性があり、シングルスレッドのRISC Zero環境では不要なオーバーヘッド
- スタブ実装は可能だが、メモリリークや二重解放のリスクがある

---

### 課題3: Boxed型 vs Unboxed型

**問題:**
`Nat`型は「boxed」として扱われ、ヒープ上のオブジェクトへのポインタになる。

```c
// Nat型を使った場合（boxed）
lean_object* lp_demo_fibonacci(lean_object* x_1)

// UInt32型を使った場合（unboxed）
uint32_t fibonacci(uint32_t n)  // ランタイム不要
```

**型の分類:**

| Lean型 | C表現 | ランタイム依存 |
|--------|-------|---------------|
| `UInt8`, `UInt16`, `UInt32`, `UInt64` | `uint8_t`〜`uint64_t` | なし ✓ |
| `Bool` | `uint8_t` | なし ✓ |
| `Nat` | `lean_object*` | あり ✗ |
| `Int` | `lean_object*` | あり ✗ |
| `String` | `lean_object*` | あり ✗ |
| `Array` | `lean_object*` | あり ✗ |

---

### 課題4: GMP（任意精度整数）依存

**問題:**
`Nat`型は任意精度整数をサポートしており、大きな数値はGMP（GNU Multiple Precision）ライブラリで処理される。

**影響:**
- GMPはRISC Zero環境にない
- GMPをRISC-Vにクロスコンパイルしても、100KB以上のバイナリサイズ増加
- proof生成時間とサイズが大幅に増加

---

### 課題5: I/O操作

**問題:**
生成コードには標準出力への書き込みが含まれる。

```c
lean_object* lean_get_stdout();  // RISC Zeroでは使用不可
```

**影響:**
- RISC Zero guestにはファイルシステムがない
- `IO`モナドを使うLeanコードは移植不可
- 純粋関数のみ対応可能

---

### 課題6: スレッド/タスクAPI

**問題:**
Leanランタイムにはタスク並列処理のAPIが含まれる。

```c
lean_task_spawn_core()  // タスク生成
lean_task_bind_core()   // タスク合成
```

**影響:**
- RISC Zero zkVMは厳密にシングルスレッド
- 並行処理を使うLeanコードは実行不可

---

### 課題7: 初期化シーケンス

**問題:**
Lean4モジュールは初期化関数を持ち、依存モジュールを順番に初期化する必要がある。

```c
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_demo_Main(uint8_t builtin);
```

**影響:**
- `Init`モジュール（Lean標準ライブラリ）の初期化が必要
- 初期化コードがランタイム全体を引き込む

---

## 解決アプローチ

### 推奨: プリミティブ型のみ使用

`UInt32`などのunboxed型のみを使用すれば、Leanランタイムへの依存を完全に排除できる。

```lean
-- ランタイム依存なし
@[export lean_fibonacci]
def fibonacci (n : UInt32) : UInt32 :=
  if n ≤ 1 then n
  else fibonacci (n - 1) + fibonacci (n - 2)
```

**利点:**
- 生成されるCコードが純粋な算術演算のみ
- `lean/lean.h`不要
- 既存のRISC Zero C FFIパターンと完全互換

**制限:**
- 任意精度整数（`Nat`）使用不可
- 配列・文字列使用不可
- 複雑なデータ構造使用不可

---

## 結論

| 実現可能性 | アプローチ |
|-----------|-----------|
| ✅ 可能 | `UInt32`/`UInt64`のみ使用した純粋関数 |
| ⚠️ 困難 | Leanランタイムのスタブ実装 |
| ❌ 不可能 | フルLeanランタイムの移植 |

Lean4の定理証明能力を活かしつつRISC Zero zkVMで実行するには、**プリミティブ型に制限した純粋関数**を使用するのが現実的な唯一の選択肢である。
