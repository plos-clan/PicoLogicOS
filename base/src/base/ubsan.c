
// #define UBSCAN_FN(_type_, _version_) __nif WEAK void __ubsan_handle_##_type_##_version_

// #define HANDLE(_type_, _version_)                                                                  \
//   UBSCAN_FN(_type_, _version_)() {}                                                                \
//   UBSCAN_FN(_type_, _version_##abort)() {}

// HANDLE(add_overflow, );
// HANDLE(alignment_assumption, );
// HANDLE(builtin_unreachable, );
// HANDLE(cfi_bad_type, );
// HANDLE(cfi_check_fail, );
// HANDLE(divrem_overflow, );
// HANDLE(dynamic_type_cache_miss, );
// HANDLE(float_cast_overflow, );
// HANDLE(function_type_mismatch, );
// HANDLE(implicit_conversion, );
// HANDLE(invalid_builtin, );
// HANDLE(invalid_objc_cast, );
// HANDLE(load_invalid_value, );
// HANDLE(missing_return, );
// HANDLE(mul_overflow, );
// HANDLE(negate_overflow, );
// HANDLE(nonnull_arg, );
// HANDLE(nonnull_return, _v1);
// HANDLE(nullability_arg, );
// HANDLE(nullability_return, _v1);
// HANDLE(out_of_bounds, );
// HANDLE(pointer_overflow, );
// HANDLE(shift_out_of_bounds, );
// HANDLE(sub_overflow, );
// HANDLE(type_mismatch, _v1);
// HANDLE(vla_bound_not_positive, );

// __nif WEAK void __ubsan_default_options() {
//   // 此函数应为空
// }

// __nif WEAK void __ubsan_on_report() {
//   // 此函数应为空
// }

// __nif WEAK void __ubsan_get_current_report_data() {
//   // 此函数应为空
// }
