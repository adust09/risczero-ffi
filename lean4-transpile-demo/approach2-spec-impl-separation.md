# アプローチ2: 仕様と実装の分離（等価証明付き）

## 概要

Lean4の定理証明能力を活かしつつ、RISC Zero zkVMで実行可能なコードを生成するアプローチ。

**核心:** 仕様（Nat）で証明し、実装（UInt32）との等価性を証明する。

---

## アーキテクチャ

```
┌─────────────────────────────────────────────────────────┐
│ Lean4                                                   │
│                                                         │
│ ┌─────────────┐    定理証明    ┌─────────────────────┐  │
│ │ Spec (Nat)  │ ─────────────→ │ Properties          │  │
│ │ - fib定義   │                │ - fib_zero          │  │
│ │ - 数学的    │                │ - fib_one           │  │
│ └─────────────┘                │ - fib_succ_succ     │  │
│       │                        └─────────────────────┘  │
│       │ 等価証明                                        │
│       ↓                                                 │
│ ┌─────────────┐                                         │
│ │ Impl(UInt32)│ ← @[export] → 純粋Cコード生成          │
│ │ - fibonacci │                                         │
│ │ - partial   │                                         │
│ └─────────────┘                                         │
│                                                         │
└─────────────────────────────────────────────────────────┘
                    │
                    ↓ RISC-V GCC クロスコンパイル
              ┌─────────────┐
              │ RISC Zero   │
              │ Guest       │
              └─────────────┘
                    │
                    ↓
              ┌─────────────┐
              │ ZK Proof    │
              └─────────────┘
```

---

## 重要な原理: Proof Erasure（証明消去）

Lean4はCコード生成前に`Prop`型の項を完全に消去する:

- 証明はランタイムオーバーヘッド**ゼロ**
- 型システム内でのみ存在
- 実行バイナリには証明コードが含まれない

これにより「証明付きだが実行時コストなし」が実現可能。

---

## ファイル構成

```
lean4-transpile-demo/
├── Fibonacci/
│   ├── Spec.lean       # 仕様 (Nat使用、証明付き)
│   ├── Impl.lean       # 実装 (UInt32、partial)
│   └── Equiv.lean      # 等価証明
├── Main.lean           # @[export]エントリポイント
├── lakefile.toml
└── lean-toolchain
```

---

## 実装詳細

### 1. 仕様定義 (Fibonacci/Spec.lean)

```lean
-- Fibonacci/Spec.lean
namespace Fibonacci.Spec

/-- Fibonacci数列の数学的定義 -/
def fib : Nat → Nat
  | 0 => 0
  | 1 => 1
  | n + 2 => fib n + fib (n + 1)

/-- fib(0) = 0 -/
theorem fib_zero : fib 0 = 0 := rfl

/-- fib(1) = 1 -/
theorem fib_one : fib 1 = 1 := rfl

/-- 漸化式 -/
theorem fib_succ_succ (n : Nat) : fib (n + 2) = fib n + fib (n + 1) := rfl

/-- fib(n) = n (n ≤ 1の場合) -/
theorem fib_le_one (n : Nat) (h : n ≤ 1) : fib n = n := by
  interval_cases n <;> rfl

end Fibonacci.Spec
```

**ポイント:**
- `Nat`を使用（任意精度、証明しやすい）
- 再帰的定義は自動的に終了性が証明される
- `rfl`（反射律）で自明な等式を証明

---

### 2. 実装 (Fibonacci/Impl.lean)

```lean
-- Fibonacci/Impl.lean
namespace Fibonacci.Impl

/-- 効率的なUInt32実装 (ループ) -/
@[export lean_fibonacci]
partial def fibonacci (n : UInt32) : UInt32 :=
  if n ≤ 1 then n
  else
    let rec loop (i curr prev : UInt32) : UInt32 :=
      if i > n then curr
      else loop (i + 1) (prev + curr) curr
    loop 2 1 0

end Fibonacci.Impl
```

**ポイント:**
- `UInt32`のみ使用（Leanランタイム依存なし）
- `partial`で終了性検査をスキップ
- `@[export lean_fibonacci]`でCシンボルをエクスポート
- 生成されるCコードは純粋な`uint32_t`演算のみ

---

### 3. 等価証明 (Fibonacci/Equiv.lean)

```lean
-- Fibonacci/Equiv.lean
import Fibonacci.Spec
import Fibonacci.Impl

namespace Fibonacci.Equiv

open Fibonacci.Spec Fibonacci.Impl

/-- 境界内で仕様と実装が等しい -/
theorem fibonacci_equiv (n : Nat) (h : n < 47) :
    (Spec.fib n).toUInt32 = Impl.fibonacci n.toUInt32 := by
  native_decide

/-- 具体的な値での検証 -/
example : Impl.fibonacci 10 = 55 := by native_decide
example : Impl.fibonacci 20 = 6765 := by native_decide

end Fibonacci.Equiv
```

**ポイント:**
- `native_decide`: Leanコンパイラで計算して証明
- `n < 47`: fib(47)はUInt32の範囲内（2971215073 < 2^32）
- 具体的な値のテストも証明として記述可能

---

### 4. エントリポイント (Main.lean)

```lean
-- Main.lean
import Fibonacci.Impl

def main : IO Unit :=
  IO.println s!"fib(10) = {Fibonacci.Impl.fibonacci 10}"
```

---

### 5. ビルド設定 (lakefile.toml)

```toml
name = "demo"
version = "0.1.0"
defaultTargets = ["demo"]

[[lean_lib]]
name = "Fibonacci"

[[lean_exe]]
name = "demo"
root = "Main"
```

---

## 信頼境界 (Trusted Computing Base)

| 層 | 信頼レベル | 内容 |
|----|-----------|------|
| **Spec** | 完全信頼 | Lean4カーネルで検証された数学的証明 |
| **Equiv** | 計算信頼 | `native_decide`使用、Leanコンパイラを信頼 |
| **Impl** | 実装信頼 | `partial`使用、終了性は保証されない |
| **C Code** | FFI信頼 | Lean4が生成したCコードを信頼 |
| **RISC Zero** | ZK信頼 | 実行の正しさをゼロ知識証明 |

**二重の証明:**
- **Lean4**: 「この関数は数学的仕様を満たす」
- **RISC Zero**: 「この入力でこの出力を計算した」

---

## 生成されるCコード（期待値）

```c
// lean_fibonacci.c (Lean4生成、クリーンアップ後)
#include <stdint.h>

static uint32_t fibonacci_loop(uint32_t n, uint32_t i, uint32_t curr, uint32_t prev) {
    while (!(n < i)) {
        uint32_t next = prev + curr;
        prev = curr;
        curr = next;
        i = i + 1;
    }
    return curr;
}

uint32_t lean_fibonacci(uint32_t n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci_loop(n, 2, 1, 0);
    }
}
```

**特徴:**
- `lean/lean.h`インクルードなし
- `lean_object*`なし
- 純粋な`uint32_t`演算のみ
- RISC Zero guestで直接コンパイル可能

---

## ワークフロー

```bash
# 1. Lean4ビルド（証明検証 + Cコード生成）
cd lean4-transpile-demo
lake build +Main:c

# 2. 生成されたCコードを確認
cat .lake/build/ir/Main.c

# 3. 必要な関数を抽出してRISC Zeroにコピー
# (手動またはスクリプトで)

# 4. RISC Zero実行
cd ..
cargo run -p host
```

---

## 制限事項

1. **UInt32のみ**: `Nat`、`Array`、`String`は使用不可
2. **partial必須**: 終了性証明をUInt32で行うのは困難
3. **手動抽出**: 生成Cコードからの関数抽出は手作業
4. **オーバーフロー**: n ≥ 47でUInt32オーバーフロー（未定義動作）

---

## 拡張可能性

### より強い証明

```lean
-- オーバーフローしないことの証明
theorem no_overflow (n : Nat) (h : n < 47) :
    Spec.fib n < 2^32 := by
  -- 帰納法で証明
  sorry

-- 単調性の証明
theorem fib_monotone (n m : Nat) (h : n ≤ m) :
    Spec.fib n ≤ Spec.fib m := by
  sorry
```

### 複数関数への適用

同じパターンで他の関数も証明可能:
- 階乗
- GCD
- べき乗
- ハッシュ関数

---

## まとめ

| 項目 | 内容 |
|------|------|
| **目的** | Lean4で証明し、RISC Zeroで実行証明 |
| **仕様** | `Nat`で数学的に定義、定理を証明 |
| **実装** | `UInt32`で効率的に実装、`@[export]` |
| **接続** | `native_decide`で等価性を計算証明 |
| **出力** | ランタイム依存なしの純粋Cコード |
