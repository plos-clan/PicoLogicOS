#pragma once

#pragma GCC system_header

#include "int.h"

typedef void (*free_t)(void *ptr);
typedef void *(*alloc_t)(size_t size);
