#pragma once
#include <base.h>

//| ============================================================================================================== |
//| Copyright (c) 2025 plos-clan                                                                                   |
//|                                                                                                                |
//| This file is part of the Pico Logic OS.                                                                        |
//|                                                                                                                |
//| Licensed under either of:                                                                                      |
//| - Apache License, Version 2.0 (see LICENSE-APACHE or http://www.apache.org/licenses/LICENSE-2.0)               |
//| - MIT License (see LICENSE-MIT or https://opensource.org/licenses/MIT)                                         |
//| at your option.                                                                                                |
//|                                                                                                                |
//| Unless required by applicable law or agreed to in writing, software distributed                                |
//| under these licenses is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES                                    |
//| OR CONDITIONS OF ANY KIND, either express or implied. See the licenses for details.                            |
//| ============================================================================================================== |

/* >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>>

 * Pico Logic OS 物理内存管理与内核内存分配器 *
 *   维护者：copi143                          *
 *   更新：2025-04-12                         *

<<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< */

typedef struct __PACKED__ kmman_pinfo {
  usize npages : 48; // 页面数，空条目 npages 为 0
  usize base   : 48; // 物理地址
  usize rc     : 32; // 引用计数
} kmman_pinfo;

typedef struct __PACKED__ kmman_minfo {
  usize size    : 48;
  usize coreid  : 8;
  usize alloced : 1;
} kmman_minfo;

/* >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>>

 ; 为了方便管理，我们将 kmman_pinfo_list 分为多个块，
 ; 每个块的大小为 KMMAN_PINFO_LIST_CAP，
 ; 块内使用数组的形式存储，
 ; 块间使用单向链表的形式存储。

<<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< */

#define KMMAN_PINFO_LIST_CAP 15

typedef struct kmman_pinfo_list kmman_pinfo_list;
struct kmman_pinfo_list {
  kmman_pinfo       pinfo[KMMAN_PINFO_LIST_CAP];
  usize             len;
  kmman_pinfo_list *next;
};

/* >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>>

<<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< */

typedef struct kmman        kmman;
typedef struct kmman_percpu kmman_percpu;

// +++++ 注意下面的核心 ID 和 CPU 核心的实际硬件 ID 不同 +++++ //

struct kmman {
  spin_t                lock;            // 全局锁
  i32                   next_core_id;    // 下一个 CPU 核心 ID (0 - 255)
  atomic volatile usize total_pages;     // 仅数据统计用 (不加锁)
  atomic volatile usize used_pages;      // 仅数据统计用 (不加锁)
  kmman_percpu         *first_lmm;       // 第一个 CPU 核心的 kmman_percpu (链表)
  kmman_percpu         *last_lmm;        // 最后一个 CPU 核心的 kmman_percpu (链表)
  kmman_pinfo_list     *pinfo_freelist;  // 空闲页面列表
  kmman_pinfo_list     *pinfo_alloclist; // 已分配页面列表
};

struct kmman_percpu {
  spin_t                lock;            // 核心锁
  i32                   coreid;          // CPU 核心 ID (0 - 255)
  atomic volatile usize owned_pages;     // 仅数据统计用 (不加锁)
  kmman_percpu         *next_lmm;        // 下一个 CPU 核心的 kmman_percpu (链表)
  kmman_pinfo_list     *pinfo_freelist;  // 空闲页面列表
  kmman_pinfo_list     *pinfo_alloclist; // 已分配页面列表
};

// 从全局内存分配器中分配内存
static void *gmm_alloc(usize size) __THROW __attr_malloc ownership_returns(gmm_alloc);
static void  gmm_free(void *ptr) __THROW ownership_takes(gmm_alloc, 1);

/* >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>>

 ; 注意内存分配规则，所有内存或页面的分配按照以下顺序查找：

 ; - 核心本地内存管理器 (kmman_percpu)
 ; - 全局内存管理器 (kmman)
 ; - 其它核心的内存管理器 (kmman_percpu)

 ; 如果没有可用内存则返回：

 ; - 物理地址 -1   (isize)  ***我们始终认为物理地址 0 是一个合法地址***
 ; - 虚拟地址 null (void *)

<<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< */

/**
 *\brief 初始化内核内存管理器
 *
 *\param gmm      全局内存管理器
 *\return 是否成功
 */
bool kmman_init(kmman *gmm);

/**
 *\brief 初始化每个 CPU 核心的 kmman_percpu 结构体
 *\note 必须先调用 kmman_init 初始化 kmman 结构体
 *
 *\param gmm      全局内存管理器
 *\param lmm      核心本地内存管理器
 *\return 是否成功
 */
bool kmman_init_percpu(kmman *gmm, kmman_percpu *lmm);

/**
 *\brief 添加物理页面到内核内存管理器
 *\note 如果内存管理器初始化后未添加可用页面就添加不可用页面，会导致添加失败
 *
 *\param gmm      全局内存管理器
 *\param addr     物理地址
 *\param npages   页面数
 *\param initial_rc 初始引用计数
 *\return 是否成功
 */
bool kmman_addpage(kmman *gmm, usize addr, usize npages, usize initial_rc);

/**
 *\brief 内核内存分配函数 (适用于分配小于 16K 的内存，强制要求)
 *
 *\param gmm      param
 *\param lmm      param
 *\param size     param
 *\return value
 */
isize kmman_malloc(kmman *gmm, kmman_percpu *lmm, usize size);

void kmman_mfree(kmman *gmm, kmman_percpu *lmm, usize addr);

isize kmman_palloc(kmman *gmm, kmman_percpu *lmm, usize npages);

void kmman_pfree(kmman *gmm, kmman_percpu *lmm, usize addr, usize npages);

void kmman_pref(kmman *gmm, kmman_percpu *lmm, usize addr);

void kmman_punref(kmman *gmm, kmman_percpu *lmm, usize addr);

/* >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>>

<<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< */

/**
 *\brief 用户提供的物理地址转换为内核虚拟地址函数
 *
 *\param paddr    物理地址
 *\return 虚拟地址
 */
VAddr _plos_kmman_phys2virt(PAddr paddr);

/**
 *\brief 内核虚拟地址转换为物理地址函数
 *
 *\param vaddr    虚拟地址
 *\return 物理地址
 */
PAddr _plos_kmman_virt2phys(VAddr vaddr);

/* >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>>

<<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< */

/**
 *\brief 内核内存分配函数 (适用于分配小于 16K 的内存，强制要求)
 *\note 分配出的内存可能有脏数据
 *
 *\param size     分配内存大小
 *\return 分配的内存地址
 */
void *kmalloc(usize size) __THROW __attr_malloc ownership_returns(kmalloc);

/**
 *\brief 内核内存释放函数 (必须是 km* 函数分配的内存)
 *
 *\param ptr      释放的内存地址
 */
void kmfree(void *ptr) __THROW ownership_takes(kmalloc, 1);

/**
 *\brief 内核物理页分配函数 (适用于分配大于 16K 的内存，但不强制)
 *\note 分配出的页面会被用二进制 0 填充
 *
 *\param size     分配内存大小 (将被自动向上对齐到页面大小)
 *\return 分配的内存地址 (页对齐)
 */
void *kpalloc(usize size) __THROW __attr_malloc ownership_returns(kpalloc);

/**
 *\brief 内核物理页释放函数 (必须是 kp* 函数分配的内存)
 *
 *\param ptr      释放的内存地址 (页对齐)
 *\param size     释放的内存大小 (将被自动向上对齐到页面大小)
 */
void kpfree(void *ptr, usize size) __THROW ownership_takes(kpalloc, 1);
