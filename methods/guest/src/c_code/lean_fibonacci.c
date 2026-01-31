// Generated from Lean4 (lean4-transpile-demo/Main.lean)
// Pure C code - no Lean runtime dependency

#include <stdint.h>

// Internal loop function
static uint32_t fibonacci_loop(uint32_t n, uint32_t i, uint32_t curr, uint32_t prev) {
    while (!(n < i)) {
        uint32_t next = prev + curr;
        prev = curr;
        curr = next;
        i = i + 1;
    }
    return curr;
}

// Exported fibonacci function
uint32_t lean_fibonacci(uint32_t n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci_loop(n, 2, 1, 0);
    }
}
