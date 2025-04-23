#pragma once
#include <define.h>

#define PWM0_BASE  0xD401A000
#define PWM1_BASE  0xD401A400
#define PWM2_BASE  0xD401A800
#define PWM3_BASE  0xD401AC00
#define PWM4_BASE  0xD401B000
#define PWM5_BASE  0xD401B400
#define PWM6_BASE  0xD401B800
#define PWM7_BASE  0xD401BC00
#define PWM8_BASE  0xD4020000
#define PWM9_BASE  0xD4020400
#define PWM10_BASE 0xD4020800
#define PWM11_BASE 0xD4020C00
#define PWM12_BASE 0xD4021000
#define PWM13_BASE 0xD4021400
#define PWM14_BASE 0xD4021800
#define PWM15_BASE 0xD4021C00
#define PWM16_BASE 0xD4022000
#define PWM17_BASE 0xD4022400
#define PWM18_BASE 0xD4022800
#define PWM19_BASE 0xD4022C00

static const uint32_t PWM_BASE[] = {
    PWM0_BASE,  PWM1_BASE,  PWM2_BASE,  PWM3_BASE,  PWM4_BASE,  PWM5_BASE,  PWM6_BASE,
    PWM7_BASE,  PWM8_BASE,  PWM9_BASE,  PWM10_BASE, PWM11_BASE, PWM12_BASE, PWM13_BASE,
    PWM14_BASE, PWM15_BASE, PWM16_BASE, PWM17_BASE, PWM18_BASE, PWM19_BASE,
};

#define PWM_CRX_OFFSET    0x00 // PWM Control Register
#define PWM_DCR_OFFSET    0x04 // PWM Duty Cycle Register
#define PWM_PCR_OFFSET    0x08 // PWM Period Register
#define PWM_OUTCNT_OFFSET 0x10 // PWM Output Counter Register

/**
 * @brief 初始化指定的 PWM 通道
 * @param channel PWM 通道编号 (0-19)
 * @param prescale 预分频器值 (0-63)
 * @param duty_cycle 占空比 (0-1023)
 * @param period 周期值 (1-1023)
 */
void pwm_init(uint8_t channel, uint8_t prescale, uint16_t duty_cycle, uint16_t period) {
  if (channel > 19 || prescale > 63 || duty_cycle > 1023 || period > 1023) {
    return; // 参数无效
  }

  uint32_t base_addr = PWM_BASE[channel];

  // 配置 PWM_CRX 寄存器
  *(volatile uint32_t *)(base_addr + PWM_CRX_OFFSET) = (1 << 8) | (prescale & 0x3F);

  // 配置 PWM_DCR 寄存器
  *(volatile uint32_t *)(base_addr + PWM_DCR_OFFSET) = (duty_cycle & 0x3FF);

  // 配置 PWM_PCR 寄存器
  *(volatile uint32_t *)(base_addr + PWM_PCR_OFFSET) = (period & 0x3FF);
}

/**
 * @brief 启用指定的 PWM 通道
 * @param channel PWM 通道编号 (0-19)
 */
void pwm_enable(uint8_t channel) {
  if (channel > 19) {
    return; // 参数无效
  }

  uint32_t base_addr = PWM_BASE[channel];

  // 启用 PWM 输出
  *(volatile uint32_t *)(base_addr + PWM_CRX_OFFSET) &= ~(1 << 8);
}

/**
 * @brief 禁用指定的 PWM 通道
 * @param channel PWM 通道编号 (0-19)
 */
void pwm_disable(uint8_t channel) {
  if (channel > 19) {
    return; // 参数无效
  }

  uint32_t base_addr = PWM_BASE[channel];

  // 禁用 PWM 输出
  *(volatile uint32_t *)(base_addr + PWM_CRX_OFFSET) |= (1 << 8);
}
