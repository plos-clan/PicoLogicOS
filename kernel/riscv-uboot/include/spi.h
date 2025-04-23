#pragma once
#include <define.h>

// SPI 基址
#define SPI_BASE 0xD401C000

// SPI 寄存器偏移
#define SPI_TXDATA  0x00 // 发送数据寄存器
#define SPI_RXDATA  0x04 // 接收数据寄存器
#define SPI_STATUS  0x08 // 状态寄存器
#define SPI_CONTROL 0x0C // 控制寄存器

// SPI 状态寄存器位定义
#define SPI_STATUS_TX_EMPTY (1 << 0) // 发送缓冲区空
#define SPI_STATUS_RX_FULL  (1 << 1) // 接收缓冲区满

// SPI 控制寄存器位定义
#define SPI_CONTROL_ENABLE  (1 << 0) // 启用 SPI
#define SPI_CONTROL_MASTER  (1 << 1) // 主模式
#define SPI_CONTROL_CS_HIGH (1 << 2) // CS 高电平

// 读写寄存器的宏
#define SPI_READ(offset)         (*(volatile uint32_t *)(SPI_BASE + (offset)))
#define SPI_WRITE(offset, value) (*(volatile uint32_t *)(SPI_BASE + (offset)) = (value))

/**
 * 初始化 SPI
 */
void spi_init() {
  // 配置 SPI 为主模式并启用
  SPI_WRITE(SPI_CONTROL, SPI_CONTROL_ENABLE | SPI_CONTROL_MASTER);
}

/**
 * 设置 SPI_CS 的电平
 * @param high 如果为 true，则设置 CS 为高电平；否则设置为低电平
 */
void spi_set_cs(bool high) {
  uint32_t control = SPI_READ(SPI_CONTROL);

  if (high) {
    control |= SPI_CONTROL_CS_HIGH; // 设置 CS 高电平
  } else {
    control &= ~SPI_CONTROL_CS_HIGH; // 设置 CS 低电平
  }

  SPI_WRITE(SPI_CONTROL, control);
}

/**
 * 向 SPI 发送单个字节
 * @param data 要发送的数据
 */
void spi_send_byte(uint8_t data) {
  // 等待发送缓冲区空
  while (!(SPI_READ(SPI_STATUS) & SPI_STATUS_TX_EMPTY))
    ;

  // 写入数据到发送寄存器
  SPI_WRITE(SPI_TXDATA, data);
}

/**
 * 从 SPI 接收单个字节
 * @return 接收到的数据
 */
uint8_t spi_receive_byte() {
  // 等待接收缓冲区满
  while (!(SPI_READ(SPI_STATUS) & SPI_STATUS_RX_FULL))
    ;

  // 从接收寄存器读取数据
  return (uint8_t)SPI_READ(SPI_RXDATA);
}

/**
 * 向 SPI 发送多个字节
 * @param data 要发送的数据缓冲区
 * @param length 数据长度
 */
void spi_send_data(const uint8_t *data, size_t length) {
  for (size_t i = 0; i < length; i++) {
    spi_send_byte(data[i]);
  }
}
