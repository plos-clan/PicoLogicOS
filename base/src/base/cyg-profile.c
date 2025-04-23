#include <base.h>

WEAK __nif void __cyg_profile_func_enter(void *callee, void *caller) {
  // 此函数应为空
}

WEAK __nif void __cyg_profile_func_exit(void *callee, void *caller) {
  // 此函数应为空
}
