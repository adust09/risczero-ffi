// Lean compiler output
// Module: Main
// Imports: public import Init
#include <lean/lean.h>
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-label"
#elif defined(__GNUC__) && !defined(__CLANG__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif
#ifdef __cplusplus
extern "C" {
#endif
LEAN_EXPORT lean_object* _lean_main();
lean_object* lean_uint32_to_nat(uint32_t);
static lean_object* lp_demo_main___closed__3;
LEAN_EXPORT lean_object* lp_demo_fibonacci_loop___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_demo_main___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_demo_IO_print___at___00IO_println___at___00main_spec__0_spec__0___boxed(lean_object*, lean_object*);
lean_object* lean_string_push(lean_object*, uint32_t);
lean_object* lean_get_stdout();
lean_object* l_Nat_reprFast(lean_object*);
LEAN_EXPORT lean_object* lp_demo_IO_println___at___00main_spec__0(lean_object*);
static lean_object* lp_demo_main___closed__0;
LEAN_EXPORT lean_object* lp_demo_IO_print___at___00IO_println___at___00main_spec__0_spec__0(lean_object*);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_demo_IO_println___at___00main_spec__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_demo_fibonacci___boxed(lean_object*);
static uint32_t lp_demo_main___closed__1;
static lean_object* lp_demo_main___closed__4;
LEAN_EXPORT uint32_t lean_fibonacci(uint32_t);
LEAN_EXPORT uint32_t lp_demo_fibonacci_loop(uint32_t, uint32_t, uint32_t, uint32_t);
uint8_t lean_uint32_dec_lt(uint32_t, uint32_t);
uint32_t lean_uint32_add(uint32_t, uint32_t);
static lean_object* lp_demo_main___closed__2;
lean_object* lean_string_append(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_demo_fibonacci_loop(uint32_t x_1, uint32_t x_2, uint32_t x_3, uint32_t x_4) {
_start:
{
uint8_t x_5; 
x_5 = lean_uint32_dec_lt(x_1, x_2);
if (x_5 == 0)
{
uint32_t x_6; uint32_t x_7; uint32_t x_8; 
x_6 = 1;
x_7 = lean_uint32_add(x_2, x_6);
x_8 = lean_uint32_add(x_4, x_3);
{
uint32_t _tmp_1 = x_7;
uint32_t _tmp_2 = x_8;
uint32_t _tmp_3 = x_3;
x_2 = _tmp_1;
x_3 = _tmp_2;
x_4 = _tmp_3;
}
goto _start;
}
else
{
return x_3;
}
}
}
LEAN_EXPORT lean_object* lp_demo_fibonacci_loop___boxed(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4) {
_start:
{
uint32_t x_5; uint32_t x_6; uint32_t x_7; uint32_t x_8; uint32_t x_9; lean_object* x_10; 
x_5 = lean_unbox_uint32(x_1);
lean_dec(x_1);
x_6 = lean_unbox_uint32(x_2);
lean_dec(x_2);
x_7 = lean_unbox_uint32(x_3);
lean_dec(x_3);
x_8 = lean_unbox_uint32(x_4);
lean_dec(x_4);
x_9 = lp_demo_fibonacci_loop(x_5, x_6, x_7, x_8);
x_10 = lean_box_uint32(x_9);
return x_10;
}
}
LEAN_EXPORT uint32_t lean_fibonacci(uint32_t x_1) {
_start:
{
uint32_t x_2; uint8_t x_3; 
x_2 = 1;
x_3 = lean_uint32_dec_le(x_1, x_2);
if (x_3 == 0)
{
uint32_t x_4; uint32_t x_5; uint32_t x_6; 
x_4 = 2;
x_5 = 0;
x_6 = lp_demo_fibonacci_loop(x_1, x_4, x_2, x_5);
return x_6;
}
else
{
return x_1;
}
}
}
LEAN_EXPORT lean_object* lp_demo_fibonacci___boxed(lean_object* x_1) {
_start:
{
uint32_t x_2; uint32_t x_3; lean_object* x_4; 
x_2 = lean_unbox_uint32(x_1);
lean_dec(x_1);
x_3 = lean_fibonacci(x_2);
x_4 = lean_box_uint32(x_3);
return x_4;
}
}
LEAN_EXPORT lean_object* lp_demo_IO_print___at___00IO_println___at___00main_spec__0_spec__0(lean_object* x_1) {
_start:
{
lean_object* x_3; lean_object* x_4; lean_object* x_5; 
x_3 = lean_get_stdout();
x_4 = lean_ctor_get(x_3, 4);
lean_inc_ref(x_4);
lean_dec_ref(x_3);
x_5 = lean_apply_2(x_4, x_1, lean_box(0));
return x_5;
}
}
LEAN_EXPORT lean_object* lp_demo_IO_println___at___00main_spec__0(lean_object* x_1) {
_start:
{
uint32_t x_3; lean_object* x_4; lean_object* x_5; 
x_3 = 10;
x_4 = lean_string_push(x_1, x_3);
x_5 = lp_demo_IO_print___at___00IO_println___at___00main_spec__0_spec__0(x_4);
return x_5;
}
}
static lean_object* _init_lp_demo_main___closed__0() {
_start:
{
lean_object* x_1; 
x_1 = lean_mk_string_unchecked("fib(10) = ", 10, 10);
return x_1;
}
}
static uint32_t _init_lp_demo_main___closed__1() {
_start:
{
uint32_t x_1; uint32_t x_2; 
x_1 = 10;
x_2 = lean_fibonacci(x_1);
return x_2;
}
}
static lean_object* _init_lp_demo_main___closed__2() {
_start:
{
uint32_t x_1; lean_object* x_2; 
x_1 = lp_demo_main___closed__1;
x_2 = lean_uint32_to_nat(x_1);
return x_2;
}
}
static lean_object* _init_lp_demo_main___closed__3() {
_start:
{
lean_object* x_1; lean_object* x_2; 
x_1 = lp_demo_main___closed__2;
x_2 = l_Nat_reprFast(x_1);
return x_2;
}
}
static lean_object* _init_lp_demo_main___closed__4() {
_start:
{
lean_object* x_1; lean_object* x_2; lean_object* x_3; 
x_1 = lp_demo_main___closed__3;
x_2 = lp_demo_main___closed__0;
x_3 = lean_string_append(x_2, x_1);
return x_3;
}
}
LEAN_EXPORT lean_object* _lean_main() {
_start:
{
lean_object* x_2; lean_object* x_3; 
x_2 = lp_demo_main___closed__4;
x_3 = lp_demo_IO_println___at___00main_spec__0(x_2);
return x_3;
}
}
LEAN_EXPORT lean_object* lp_demo_IO_println___at___00main_spec__0___boxed(lean_object* x_1, lean_object* x_2) {
_start:
{
lean_object* x_3; 
x_3 = lp_demo_IO_println___at___00main_spec__0(x_1);
return x_3;
}
}
LEAN_EXPORT lean_object* lp_demo_IO_print___at___00IO_println___at___00main_spec__0_spec__0___boxed(lean_object* x_1, lean_object* x_2) {
_start:
{
lean_object* x_3; 
x_3 = lp_demo_IO_print___at___00IO_println___at___00main_spec__0_spec__0(x_1);
return x_3;
}
}
LEAN_EXPORT lean_object* lp_demo_main___boxed(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = _lean_main();
return x_2;
}
}
lean_object* initialize_Init(uint8_t builtin);
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_demo_Main(uint8_t builtin) {
lean_object * res;
if (_G_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_initialized = true;
res = initialize_Init(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
lp_demo_main___closed__0 = _init_lp_demo_main___closed__0();
lean_mark_persistent(lp_demo_main___closed__0);
lp_demo_main___closed__1 = _init_lp_demo_main___closed__1();
lp_demo_main___closed__2 = _init_lp_demo_main___closed__2();
lean_mark_persistent(lp_demo_main___closed__2);
lp_demo_main___closed__3 = _init_lp_demo_main___closed__3();
lean_mark_persistent(lp_demo_main___closed__3);
lp_demo_main___closed__4 = _init_lp_demo_main___closed__4();
lean_mark_persistent(lp_demo_main___closed__4);
return lean_io_result_mk_ok(lean_box(0));
}
char ** lean_setup_args(int argc, char ** argv);
void lean_initialize_runtime_module();

  #if defined(WIN32) || defined(_WIN32)
  #include <windows.h>
  #endif

  int main(int argc, char ** argv) {
  #if defined(WIN32) || defined(_WIN32)
  SetErrorMode(SEM_FAILCRITICALERRORS);
  SetConsoleOutputCP(CP_UTF8);
  #endif
  lean_object* in; lean_object* res;
argv = lean_setup_args(argc, argv);
lean_initialize_runtime_module();
lean_set_panic_messages(false);
res = initialize_demo_Main(1 /* builtin */);
lean_set_panic_messages(true);
lean_io_mark_end_initialization();
if (lean_io_result_is_ok(res)) {
lean_dec_ref(res);
lean_init_task_manager();
res = _lean_main();
}
lean_finalize_task_manager();
if (lean_io_result_is_ok(res)) {
  int ret = 0;
  lean_dec_ref(res);
  return ret;
} else {
  lean_io_result_show_error(res);
  lean_dec_ref(res);
  return 1;
}
}
#ifdef __cplusplus
}
#endif
