#pragma once
#include <define.h>

#include "timer.h"

#define WATCHDOG_FAR_OFFSET 0xB0
#define WATCHDOG_SAR_OFFSET 0xB4
#define WATCHDOG_MER_OFFSET 0xB8
#define WATCHDOG_MR_OFFSET  0xBC
#define WATCHDOG_SR_OFFSET  0xC0
#define WATCHDOG_ICR_OFFSET 0xC4
#define WATCHDOG_CRR_OFFSET 0xC8
#define WATCHDOG_VR_OFFSET  0xCC

#define WATCHDOG_KEY1 0xBABA
#define WATCHDOG_KEY2 0xEB10

static volatile struct {
  u32 far;
  u32 sar;
  u32 mer;
  u32 mr;
  u32 sr;
  u32 icr;
  u32 crr;
  u32 vr;
} *const watchdog = (void *)(PMU_TIMERS_BASE + WATCHDOG_FAR_OFFSET);

void watchdog_unlock() {
  *(volatile u32 *)(PMU_TIMERS_BASE + WATCHDOG_FAR_OFFSET) = WATCHDOG_KEY1;
  *(volatile u32 *)(PMU_TIMERS_BASE + WATCHDOG_SAR_OFFSET) = WATCHDOG_KEY2;
}

void watchdog_disable() {
  watchdog_unlock();
  *(volatile u32 *)(PMU_TIMERS_BASE + WATCHDOG_MER_OFFSET) = 0;
}

void watchdog_enable(bool reset_mode) {
  *(volatile u32 *)(PMU_TIMERS_BASE + WATCHDOG_MER_OFFSET) = (reset_mode << 1) | 1;
}
