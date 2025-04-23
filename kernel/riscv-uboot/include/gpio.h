#pragma once
#include <define.h>

// SpacemiT Key Stone® K1

#define GPIO0_BASE 0xD4019000
#define GPIO1_BASE 0xD4019004
#define GPIO2_BASE 0xD4019008
#define GPIO3_BASE 0xD4019100

static const u32 GPIO_BASE[] = {GPIO0_BASE, GPIO1_BASE, GPIO2_BASE, GPIO3_BASE};

#define GPIO_PLR_OFFSET   0x00 // GPIO 状态寄存器 (R)
#define GPIO_PDR_OFFSET   0x0C // GPIO 方向寄存器 (R/W)
#define GPIO_PSR_OFFSET   0x18 // GPIO 拉高电平 (W)
#define GPIO_PCR_OFFSET   0x24 // GPIO 拉低电平 (W)
#define GPIO_RER_OFFSET   0x30 // GPIO 上升沿中断 (R/W)
#define GPIO_FER_OFFSET   0x3C // GPIO 下降沿中断 (R/W)
#define GPIO_EDR_OFFSET   0x48 // GPIO 边缘触发中断 (R/W)
#define GPIO_SDR_OFFSET   0x54 // GPIO 输出模式 (W)
#define GPIO_CDR_OFFSET   0x60 // GPIO 输入模式 (W)
#define GPIO_SRERX_OFFSET 0x6C // GPIO 启用上升沿检测 (W)
#define GPIO_CRERX_OFFSET 0x78 // GPIO 禁用上升沿检测 (W)
#define GPIO_SFERX_OFFSET 0x84 // GPIO 启用下降沿检测 (W)
#define GPIO_CFERX_OFFSET 0x90 // GPIO 禁用下降沿检测 (W)

typedef volatile struct gpio {
  u32 plr; // GPIO 状态寄存器
  u32 _pad0[2];
  u32 pdr; // GPIO 方向寄存器
  u32 _pad1[2];
  u32 psr; // GPIO 拉高电平
  u32 _pad2[2];
  u32 pcr; // GPIO 拉低电平
  u32 _pad3[2];
  u32 rer; // GPIO 上升沿中断
  u32 _pad4[2];
  u32 fer; // GPIO 下降沿中断
  u32 _pad5[2];
  u32 edr; // GPIO 边缘触发中断
  u32 _pad6[2];
  u32 sdr; // GPIO 输出模式
  u32 _pad7[2];
  u32 cdr; // GPIO 输入模式
  u32 _pad8[2];
  u32 srerx; // GPIO 启用上升沿检测
  u32 _pad9[2];
  u32 crerx; // GPIO 禁用上升沿检测
  u32 _pad10[2];
  u32 sferx; // GPIO 启用下降沿检测
  u32 _pad11[2];
  u32 cferx; // GPIO 禁用下降沿检测
  u32 _pad12[2];
} *gpio_t;

#define GPIO(group) ((gpio_t)GPIO_BASE[group])

bool gpio_get(u32 pin) {
  u32 group = pin / 32;
  u32 bit   = pin % 32;
  return (GPIO(group)->plr >> bit) & 0x1;
}

bool gpio_is_high(u32 pin) {
  return gpio_get(pin);
}

bool gpio_is_low(u32 pin) {
  return !gpio_get(pin);
}

void gpio_set(u32 pin) {
  u32 group        = pin / 32;
  u32 bit          = pin % 32;
  GPIO(group)->psr = (1 << bit);
}

void gpio_clr(u32 pin) {
  u32 group        = pin / 32;
  u32 bit          = pin % 32;
  GPIO(group)->pcr = (1 << bit);
}

bool gpio_read(u32 pin) {
  u32 group = pin / 32;
  u32 bit   = pin % 32;
  return (GPIO(group)->plr >> bit) & 0x1;
}

void gpio_write(u32 pin, bool value) {
  u32 group = pin / 32;
  u32 bit   = pin % 32;
  if (value) {
    GPIO(group)->psr = (1 << bit);
  } else {
    GPIO(group)->pcr = (1 << bit);
  }
}

void gpio_set_mode(u32 pin, bool output) {
  u32 group = pin / 32;
  u32 bit   = pin % 32;
  if (output) {
    GPIO(group)->pdr |= (1 << bit);
  } else {
    GPIO(group)->pdr &= ~(1 << bit);
  }
}

bool gpio_is_write(u32 pin) {
  u32 group = pin / 32;
  u32 bit   = pin % 32;
  return (GPIO(group)->pdr >> bit) & 0x1;
}

bool gpio_is_read(u32 pin) {
  return !gpio_is_write(pin);
}
