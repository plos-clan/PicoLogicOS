#pragma once
#include <base/thread/spin.h>

static spin_t lock;
static size_t flags;

static void klock() {
  var flag = asm_get_flags();
  asm_cli;
  spin_lock(lock);
  flags = flag;
}

static void kunlock() {
  var flag = flags;
  spin_unlock(lock);
  asm_set_flags(flag);
}
