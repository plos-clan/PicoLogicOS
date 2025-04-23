#pragma once
#include <define.h>

#include "gpio.h"
#include "spi.h"

void delay(uint32_t dt) {
  for (volatile uint32_t i = 0; i < dt * 1000; i++) {
    asm volatile("nop");
  }
}

// 命令发送函数
void st7789_sendcommand(uint8_t cmd) {
  // 设置DC为低电平，表示发送命令
  gpio_write(49, 0);

  // 开始传输（片选信号如果有的话，这里设置为低）
  // spi_set_cs(0);

  // 发送命令
  // spi_send_byte(cmd);
  for (int i = 7; i >= 0; i--) {
    gpio_write(75, 0);
    gpio_write(77, (cmd >> i) & 0x01);
    delay(1);
    gpio_write(75, 1); // 时钟上升沿，数据被锁存
    delay(1);
  }

  // 结束传输（片选信号如果有的话，这里设置为高）
  // spi_set_cs(1);
}

// 数据发送函数
void st7789_senddata(uint8_t data) {
  // 设置DC为高电平，表示发送数据
  gpio_write(49, 1);

  // 开始传输
  // spi_set_cs(0);

  // 按送数据
  // spi_send_byte(data);
  for (int i = 7; i >= 0; i--) {
    gpio_write(75, 0);
    gpio_write(77, (data >> i) & 0x01);
    delay(1);
    gpio_write(75, 1); // 时钟上升沿，数据被锁存
    delay(1);
  }

  // 结束传输
  // spi_set_cs(1);
}

typedef struct st7789 {
  u32 width;  // 显示宽度
  u32 height; // 显示高度
  i32 dc_pin; // 数据/命令引脚
  i32 bl_pin; // 背光引脚
  i32 cs_pin; // 片选引脚
} *st7789_t;

// 初始化显示屏
void st7789_init() {
  gpio_set_mode(49, true); // DC引脚
  gpio_set_mode(74, true); // 背光引脚
  gpio_set_mode(75, true); // SPI数据引脚
  gpio_set_mode(77, true); // SPI时钟引脚
  gpio_set_mode(91, true); // 复位引脚

  // 复位显示屏
  // gpio_write(91, 0);
  // delay(250);
  // gpio_write(91, 1);
  // delay(1000);

  // 发送初始化命令序列
  // 注意：以下命令序列需要根据您的具体显示屏控制器型号调整
  st7789_sendcommand(0x11); // Sleep out
  delay(120);               // 等待显示稳定

  st7789_sendcommand(0x36); // Memory Access Control
  st7789_senddata(0x00);    // 设置扫描方向等

  st7789_sendcommand(0x3A); // Pixel Format Set
  st7789_senddata(0x05);    // 16-bit/pixel (65K颜色，RGB565格式)

  // 设置显示区域
  st7789_sendcommand(0x2A); // Column Address Set
  st7789_senddata(0x00);    // 起始列高字节
  st7789_senddata(0x00);    // 起始列低字节
  st7789_senddata(0x00);    // 结束列高字节
  st7789_senddata(0xEF);    // 结束列低字节(239)

  st7789_sendcommand(0x2B); // Row Address Set
  st7789_senddata(0x00);    // 起始行高字节
  st7789_senddata(0x00);    // 起始行低字节
  st7789_senddata(0x00);    // 结束行高字节
  st7789_senddata(0xEF);    // 结束行低字节(239)

  st7789_sendcommand(0x29); // Display ON

  // 开启背光
  gpio_write(74, 1);
}

// 设置地址窗口函数
void st7789_SetWindow(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end) {
  // 设置列地址
  st7789_sendcommand(0x2A);
  st7789_senddata(x_start >> 8);   // 起始列高字节
  st7789_senddata(x_start & 0xFF); // 起始列低字节
  st7789_senddata(x_end >> 8);     // 结束列高字节
  st7789_senddata(x_end & 0xFF);   // 结束列低字节

  // 设置行地址
  st7789_sendcommand(0x2B);
  st7789_senddata(y_start >> 8);   // 起始行高字节
  st7789_senddata(y_start & 0xFF); // 起始行低字节
  st7789_senddata(y_end >> 8);     // 结束行高字节
  st7789_senddata(y_end & 0xFF);   // 结束行低字节

  // 准备写入数据
  st7789_sendcommand(0x2C); // Memory Write
}

// 发送缓冲区函数 - 假设缓冲区中的数据是RGB565格式
void st7789_SendBuffer(uint16_t *buffer, uint32_t size) {
  // 设置为数据模式
  gpio_write(49, 1);

  // 发送所有像素数据
  for (uint32_t i = 0; i < size; i++) {
    // 发送高字节
    uint8_t high = buffer[i] >> 8;
    // spi_send_byte(high);
    for (int i = 7; i >= 0; i--) {
      gpio_write(75, 0);
      gpio_write(77, (high >> i) & 0x01);
      gpio_write(75, 1);
    }

    // 发送低字节
    uint8_t low = buffer[i] & 0xFF;
    // spi_send_byte(low);
    for (int i = 7; i >= 0; i--) {
      gpio_write(75, 0);
      gpio_write(77, (low >> i) & 0x01);
      gpio_write(75, 1);
    }
  }
}
