# risczero-ffi

RISC Zero zkVM sample that proves a Fibonacci computation where the guest calls a C function via FFI. The host supplies the input, generates a proof, reads the committed result, and verifies the receipt.

## Features

- **C FFI**: Guest program calls C functions compiled for RISC-V
- **Lean4 Integration**: Includes Lean4-to-C transpilation pipeline

## Run

```sh
cargo run -p host
```

Optional release build:

```sh
cargo run -p host --release
```

## Lean4 to RISC Zero Pipeline

This project demonstrates running Lean4-generated C code in RISC Zero zkVM.

### Pipeline

```
Lean4 (UInt32) → lake build → C code → RISC-V GCC → RISC Zero Guest → Proof
```

### Build Lean4 Code

```sh
cd lean4-fib
lake build +Main:c
```

Generated C code is output to `.lake/build/ir/Main.c`.

### Constraints

When using Lean4 with RISC Zero, you must:

- Use only primitive types (`UInt32`, `UInt64`, `Bool`)
- Avoid `Nat`, `Array`, `String` (require Lean runtime)
- Use `partial` or provide termination proofs for recursion
- Extract only the pure functions from generated C code

### Example Lean4 Code

```lean
@[export lean_fibonacci]
partial def fibonacci (n : UInt32) : UInt32 :=
  if n ≤ 1 then n
  else
    let rec loop (i curr prev : UInt32) : UInt32 :=
      if i > n then curr
      else loop (i + 1) (prev + curr) curr
    loop 2 1 0
```

This generates pure C code without Lean runtime dependencies.

## Project Structure

```
risczero-ffi/
├── host/                     # Host program (prover/verifier)
├── methods/
│   ├── guest/
│   │   ├── src/
│   │   │   ├── main.rs       # Guest entry point
│   │   │   └── c_code/
│   │   │       ├── fibonacci.c       # Original C implementation
│   │   │       └── lean_fibonacci.c  # Lean4-generated C
│   │   └── build.rs          # RISC-V cross-compilation
│   └── src/lib.rs
└── lean4-fib/     # Lean4 project
    ├── Main.lean
    ├── lakefile.toml
    └── lean-toolchain
```
