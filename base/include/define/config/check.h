

#if !__BYTE_ORDER__ || !__ORDER_LITTLE_ENDIAN__ || !__ORDER_BIG_ENDIAN__ || !__ORDER_PDP_ENDIAN__
#  error "未知的端序"
#endif

#undef LITTLE_ENDIAN
#undef BIG_ENDIAN

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#  define LITTLE_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  define BIG_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
#  error "不支持 PDP 端序"
#else
#  error "未知的端序"
#endif

#if KERNEL || LOADER
#  define RING0 1
#endif

#if RING3 && KERNEL
#  error "不允许同时定义 RING3 和 KERNEL"
#endif

#if RING3 && LOADER
#  error "不允许同时定义 RING3 和 LOADER"
#endif
