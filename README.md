# risczero-ffi

RISC Zero zkVM sample that proves a Fibonacci computation where the guest calls a C function via FFI. The host supplies the input, generates a proof, reads the committed result, and verifies the receipt.

## Run

```sh
cargo run -p host
```

Optional release build:

```sh
cargo run -p host --release
```
