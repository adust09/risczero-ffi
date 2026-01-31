use methods::{GUEST_ELF, GUEST_ID};
use risc0_zkvm::{default_prover, ExecutorEnv};

fn main() {
    // Input: Fibonacci index
    let n: u32 = 10;

    // Build execution environment with input
    let env = ExecutorEnv::builder()
        .write(&n)
        .unwrap()
        .build()
        .unwrap();

    // Generate proof
    let prover = default_prover();
    let prove_info = prover.prove(env, GUEST_ELF).unwrap();

    // Extract receipt and result
    let receipt = prove_info.receipt;
    let result: u32 = receipt.journal.decode().unwrap();

    println!("Fibonacci({}) = {}", n, result);

    // Verify the proof
    receipt.verify(GUEST_ID).unwrap();
    println!("Proof verified!");
}
