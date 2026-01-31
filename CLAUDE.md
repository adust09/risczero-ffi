# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

RISC Zero zkVM sample demonstrating C FFI integration. The guest program calls a C function (Fibonacci) via FFI, and the host generates and verifies zero-knowledge proofs of the computation.

## Build and Run Commands

```sh
# Run the prover (debug build)
cargo run -p host

# Run with optimizations (faster proving)
cargo run -p host --release

# Build without running
cargo build -p host

# Check compilation
cargo check
```

## Architecture

```
risczero-ffi/
├── host/src/main.rs      # Prover: sends input, generates proof, verifies receipt
├── methods/
│   ├── build.rs          # Embeds guest ELF via risc0_build::embed_methods()
│   ├── src/lib.rs        # Exports GUEST_ELF and GUEST_ID constants
│   └── guest/
│       ├── build.rs      # Cross-compiles C code to RISC-V using cc crate
│       ├── src/main.rs   # Guest: reads input, calls C FFI, commits result
│       └── src/c_code/   # C source files compiled for RISC-V target
```

### Data Flow

1. Host writes input (`n`) to `ExecutorEnv`
2. Guest reads input via `env::read()`
3. Guest calls C function via FFI (`c_fibonacci`)
4. Guest commits result via `env::commit()`
5. Host extracts result from `receipt.journal.decode()`
6. Host verifies proof with `receipt.verify(GUEST_ID)`

### C FFI Build Process

The guest's `build.rs` uses the RISC Zero RISC-V GCC toolchain located at `~/.risc0/cpp/bin/riscv32-unknown-elf-gcc`. C files are compiled with:
- Target: `rv32im` (RISC-V 32-bit with M extension)
- ABI: `ilp32`
- Flags: `-ffreestanding -nostdlib`

## Prerequisites

- Rust toolchain
- RISC Zero toolchain: `cargo install cargo-risczero && cargo risczero install`
