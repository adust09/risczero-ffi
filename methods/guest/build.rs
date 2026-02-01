fn main() {
    let home = std::env::var("HOME").expect("HOME environment variable not set");
    let compiler = format!("{}/.risc0/cpp/bin/riscv32-unknown-elf-gcc", home);

    // Build original C fibonacci
    cc::Build::new()
        .compiler(&compiler)
        .flag("-march=rv32im")
        .flag("-mabi=ilp32")
        .flag("-ffreestanding")
        .flag("-nostdlib")
        .file("src/c_code/fibonacci.c")
        .compile("fibonacci");

    // Build Lean4-generated Main.c (contains lean_fibonacci)
    cc::Build::new()
        .compiler(&compiler)
        .flag("-march=rv32im")
        .flag("-mabi=ilp32")
        .flag("-ffreestanding")
        .flag("-nostdlib")
        .include("src/c_code")
        .file("src/c_code/lean_main.c")
        .compile("lean_main");

    println!("cargo:rerun-if-changed=src/c_code/fibonacci.c");
    println!("cargo:rerun-if-changed=src/c_code/lean_main.c");
}
