#include <kernel.h>

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

#if 0
void kmman_pinfo_foreach(kmman_pinfo_list *list) {
  for (kmman_pinfo_list *_l_ = list; _l_ != null; _l_ = _l_->next) {
    if (_l_->len == 0) continue;
    usize _i_ = 0;
    for (; _i_ < KMMAN_PINFO_LIST_CAP; _i_++) {
      if (_l_->pinfo[_i_].npages == 0) continue;
      kmman_pinfo *pinfo = &_l_->pinfo[_i_];
    }
    if (_i_ < KMMAN_PINFO_LIST_CAP) break;
  }
}
#endif

#define kmman_pinfo_foreach(_list_, _node_, ...)                                                   \
  ({                                                                                               \
    for (kmman_pinfo_list *_l_ = (_list_); _l_ != null; _l_ = _l_->next) {                         \
      if (_l_->len == 0) continue;                                                                 \
      usize _i_ = 0;                                                                               \
      for (; _i_ < KMMAN_PINFO_LIST_CAP; _i_++) {                                                  \
        if (_l_->pinfo[_i_].npages == 0) continue;                                                 \
        kmman_pinfo *_node_ = &_l_->pinfo[_i_];                                                    \
        (__VA_ARGS__);                                                                             \
      }                                                                                            \
      if (_i_ < KMMAN_PINFO_LIST_CAP) break;                                                       \
    }                                                                                              \
  })

// 将物理页数据添加到列表中
// 此函数会调用 gmm_alloc() 分配内存
static bool pinfo_add(kmman_pinfo_list **list_p, kmman_pinfo info) {
  val list = *list_p;

  // ----- 如果列表已满 ----- //
  if (list->len == KMMAN_PINFO_LIST_CAP) {
    // ----- 添加到列表中 ----- //
    kmman_pinfo_list *new_list = gmm_alloc(sizeof(kmman_pinfo_list));
    if (new_list == null) return false;
    new_list->pinfo[0] = info;
    new_list->len      = 1;
    new_list->next     = list;
    *list_p            = new_list;
    for (usize i = 1; i < KMMAN_PINFO_LIST_CAP; i++) {
      new_list->pinfo[i] = (kmman_pinfo){};
    }
    return true;
    // ++++ 主逻辑结束 ++++ //
  }

  // ----- 添加到列表中 ----- //
  for (usize i = 0; i < KMMAN_PINFO_LIST_CAP; i++) {
    if (list->pinfo[i].npages == 0) {
      list->pinfo[i] = info;
      list->len++;
      break;
    }
  }

  // ----- 保证有空闲的块永远在最前 ----- //
  if (list->len == KMMAN_PINFO_LIST_CAP && list->next && list->next->len < KMMAN_PINFO_LIST_CAP) {
    var node = list->next;
    *list_p  = node;
    while (node->next && node->next->len < KMMAN_PINFO_LIST_CAP) {
      node = node->next;
    }
    list->next = node->next;
    node->next = list;
  }

  return true;
  // ++++ 主逻辑结束 ++++ //
}

// 将物理页数据从列表中删除 (先查找，查找不到返回 false)
// 此函数会调用 gmm_free() 释放内存
static bool pinfo_del(kmman_pinfo_list **list_p, kmman_pinfo info) {}

static void *gmm_alloc(usize size) {}

static void gmm_free(void *ptr) {}

bool kmman_init(kmman *gmm) {
  assert(gmm != null, "kmman_init gmm must not null");
  gmm->lock         = SPIN_INIT;
  gmm->next_core_id = 0;
  gmm->first_lmm    = null;
  gmm->last_lmm     = null;
  return true;
}

bool kmman_init_percpu(kmman *gmm, kmman_percpu *lmm) {
  assert(gmm != null, "kmman_init_percpu gmm must not null");
  assert(lmm != null, "kmman_init_percpu lmm must not null");
  lmm->lock     = SPIN_INIT;
  lmm->coreid   = -1; // 后续初始化
  lmm->next_lmm = null;

  spin_lock(lmm->lock);
  spin_lock(gmm->lock);
  lmm->coreid = gmm->next_core_id++;
  if (gmm->first_lmm == null) {
    gmm->first_lmm = lmm;
    gmm->last_lmm  = lmm;
  } else {
    gmm->last_lmm->next_lmm = lmm;
    gmm->last_lmm           = lmm;
  }
  spin_unlock(gmm->lock);
  spin_unlock(lmm->lock);

  return true;
}

bool kmman_addpage(kmman *gmm, usize addr, usize npages, usize initial_rc) {
  assert(gmm != null, "kmman_addpage gmm must not null");
  assert(addr > 0, "kmman_addpage addr must > 0");
  assert(npages > 0, "kmman_addpage npages must > 0");
  assert((u32)initial_rc == initial_rc, "kmman_addpage initial_rc must <= 0xFFFFFFFF");

  if (gmm->total_pages == 0 && initial_rc != 0) return false;

  spin_lock(gmm->lock);

  gmm->total_pages += npages;
  if (initial_rc > 0) gmm->used_pages += npages;

  spin_unlock(gmm->lock);

  return true;
}

isize kmman_malloc(kmman *gmm, kmman_percpu *lmm, usize size) {
  return -1;
}

void kmman_mfree(kmman *gmm, kmman_percpu *lmm, usize addr) {}

isize kmman_palloc(kmman *gmm, kmman_percpu *lmm, usize npages) {
  assert(gmm != null, "gmm must not null");
  assert(lmm != null, "lmm must not null");
  assert(npages > 0, "try to alloc 0 pages");

  spin_lock(lmm->lock);
  spin_unlock(lmm->lock);

  return -1;
}

void kmman_pfree(kmman *gmm, kmman_percpu *lmm, usize addr, usize npages) {
  assert((addr & PAGE_SIZE) == 0, "kpfree ptr must page aligned");
  assert(npages > 0, "try to free 0 pages");
}

void kmman_pref(kmman *gmm, kmman_percpu *lmm, usize addr) {
  assert(gmm != null, "kmman_pref gmm must not null");
  assert(lmm != null, "kmman_pref lmm must not null");
}

void kmman_punref(kmman *gmm, kmman_percpu *lmm, usize addr) {
  assert(gmm != null, "kmman_punref gmm must not null");
  assert(lmm != null, "kmman_punref lmm must not null");
}
