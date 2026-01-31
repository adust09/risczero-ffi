#![no_main]
#![no_std]

use risc0_zkvm::guest::env;
risc0_zkvm::guest::entry!(main);

extern "C" {
    fn c_fibonacci(n: u32) -> u32;
}

fn main() {
    let n: u32 = env::read();
    let result = unsafe { c_fibonacci(n) };
    env::commit(&result);
}
