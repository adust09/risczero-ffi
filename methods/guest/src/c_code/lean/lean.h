/*
 * Minimal Lean runtime stub for RISC Zero zkVM
 *
 * This header provides macro definitions for Lean runtime functions
 * used in Lean4-generated C code. It allows compiling Lean4-generated
 * code without the full Lean runtime (which requires OS support).
 *
 * Only pure arithmetic operations are supported. IO and memory
 * management functions are stubbed as they are not used in our
 * fibonacci implementation.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Export macro */
#define LEAN_EXPORT

/* UInt32 Arithmetic operations */
#define lean_uint32_add(a, b)    ((uint32_t)((a) + (b)))
#define lean_uint32_sub(a, b)    ((uint32_t)((a) - (b)))
#define lean_uint32_mul(a, b)    ((uint32_t)((a) * (b)))
#define lean_uint32_div(a, b)    ((uint32_t)((a) / (b)))
#define lean_uint32_mod(a, b)    ((uint32_t)((a) % (b)))

/* UInt32 Comparison operations (return uint8_t for Lean's Bool) */
#define lean_uint32_dec_lt(a, b) ((uint8_t)((a) < (b)))
#define lean_uint32_dec_le(a, b) ((uint8_t)((a) <= (b)))
#define lean_uint32_dec_eq(a, b) ((uint8_t)((a) == (b)))

/* UInt64 Arithmetic operations */
#define lean_uint64_add(a, b)    ((uint64_t)((a) + (b)))
#define lean_uint64_sub(a, b)    ((uint64_t)((a) - (b)))
#define lean_uint64_mul(a, b)    ((uint64_t)((a) * (b)))
#define lean_uint64_div(a, b)    ((uint64_t)((a) / (b)))
#define lean_uint64_mod(a, b)    ((uint64_t)((a) % (b)))

/* UInt64 Comparison operations */
#define lean_uint64_dec_lt(a, b) ((uint8_t)((a) < (b)))
#define lean_uint64_dec_le(a, b) ((uint8_t)((a) <= (b)))
#define lean_uint64_dec_eq(a, b) ((uint8_t)((a) == (b)))

/*
 * Lean object type stub
 * Not used in pure arithmetic functions, but needed for compilation
 * of boxed versions (which we don't call)
 */
typedef void* lean_object;

/* Reference counting stubs (no-ops in zkVM context) */
#define lean_inc_ref(o)     ((void)0)
#define lean_dec_ref(o)     ((void)0)
#define lean_dec(o)         ((void)0)
#define lean_inc(o)         ((void)0)

/* Boxing/unboxing stubs for unused functions */
static inline uint32_t lean_unbox_uint32(lean_object* o) { return (uint32_t)(uintptr_t)o; }
static inline lean_object* lean_box_uint32(uint32_t n) { return (lean_object*)(uintptr_t)n; }

/* Mark persistent (no-op) */
#define lean_mark_persistent(o) ((void)0)

/* IO result stubs */
static inline lean_object* lean_io_result_mk_ok(lean_object* o) { return o; }
static inline int lean_io_result_is_ok(lean_object* o) { return 1; }
static inline int lean_io_result_is_error(lean_object* o) { return 0; }
static inline void lean_io_result_show_error(lean_object* o) {}
static inline void lean_io_mark_end_initialization(void) {}

/* String stubs (unused in our fibonacci) */
static inline lean_object* lean_mk_string_unchecked(const char* s, size_t len, size_t cap) { return 0; }
static inline lean_object* lean_string_push(lean_object* s, uint32_t c) { return 0; }
static inline lean_object* lean_string_append(lean_object* a, lean_object* b) { return 0; }

/* Nat conversion stubs */
static inline lean_object* lean_uint32_to_nat(uint32_t n) { return 0; }

/* Stdout stub */
static inline lean_object* lean_get_stdout(void) { return 0; }
static inline lean_object* lean_ctor_get(lean_object* o, int i) { return 0; }
static inline lean_object* lean_apply_2(lean_object* f, lean_object* a1, lean_object* a2) { return 0; }
static inline lean_object* lean_box(size_t n) { return 0; }

/* Repr stub */
static inline lean_object* l_Nat_reprFast(lean_object* n) { return 0; }

/* Task manager stubs */
static inline void lean_init_task_manager(void) {}
static inline void lean_finalize_task_manager(void) {}

/* Panic stubs */
static inline void lean_set_panic_messages(int b) {}

/* Setup stubs - redefine main() to avoid conflict */
#define lean_setup_args(argc, argv) (argv)
#define lean_initialize_runtime_module()
#define initialize_Init(b) lean_io_result_mk_ok(0)

/*
 * Rename main() in Main.c to avoid conflict with guest's main()
 * This is done via a macro that transforms the function definition
 */
#define main lean_main_unused
