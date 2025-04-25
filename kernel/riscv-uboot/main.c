#include <lcd.h>
#include <mfpr.h>
#include <pwm.h>
#include <uart.h>
#include <watchdog.h>

int main() {
  watchdog_disable(); // 关闭看门狗

  // // 初始化UART0，波特率115200
  // uart_init(UART0_BASE, 115200);

  uart_puts(UART0_BASE, "Loading...\r\n");

  // pwm_init(9, 10, 512, 1023);
  // pwm_enable(9);

  // *(volatile uint32_t *)MFPR_GPIO00_BASE = (5 << 13) | (2 << 11) | (1 << 6);
  // *(volatile uint32_t *)MFPR_GPIO49_BASE = (5 << 13) | (2 << 11) | (1 << 6);
  // *(volatile uint32_t *)MFPR_GPIO74_BASE = (5 << 13) | (2 << 11) | (1 << 6);
  // *(volatile uint32_t *)MFPR_GPIO75_BASE = (5 << 13) | (2 << 11) | (1 << 6);
  // *(volatile uint32_t *)MFPR_GPIO77_BASE = (5 << 13) | (2 << 11) | (1 << 6);
  // *(volatile uint32_t *)MFPR_GPIO91_BASE = (5 << 13) | (2 << 11) | (1 << 6);

  for (int i = 0; i < 128; i++) {
    gpio_set_mode(i, true);
    gpio_clr(i);
  }

  // 假设我们有一个240x240的RGB565缓冲区
  static uint16_t frameBuffer[240 * 240];

  st7789_init();

  while (1) {
    st7789_SetWindow(0, 0, 239, 239);
    gpio_write(49, 1);
    for (uint32_t i = 0; i < 240 * 240 * 16; i++) {
      gpio_write(75, 0);
      gpio_write(77, 1);
      gpio_write(75, 1);
    }
    st7789_SetWindow(0, 0, 239, 239);
    gpio_write(49, 1);
    for (uint32_t i = 0; i < 240 * 240 * 16; i++) {
      gpio_write(75, 0);
      gpio_write(77, 0);
      gpio_write(75, 1);
    }
  }

  // 设置要显示的区域为整个屏幕
  uart_puts(UART0_BASE, "Setting window...\r\n");
  st7789_SetWindow(0, 0, 239, 239);

  // 发送缓冲区数据
  uart_puts(UART0_BASE, "Sending buffer...\r\n");
  st7789_SendBuffer(frameBuffer, 240 * 240);

  // 发送欢迎消息
  uart_puts(UART0_BASE, "SpacemiT Key Stone K1 UART Test\r\n");
  uart_puts(UART0_BASE, "Please type something and press Enter...\r\n");

  char buffer[100];
  int  idx = 0;

  while (1) {
    char c = uart_getc(UART0_BASE);
    uart_putc(UART0_BASE, c);

    if (c == '\r') {
      uart_putc(UART0_BASE, '\n');
      buffer[idx] = '\0';

      i32 color = 0;
      for (int i = 0; buffer[i] != '\0'; i++) {
        color      <<= 4;
        char digit   = buffer[i];
        if (digit >= '0' && digit <= '9') {
          color |= (digit - '0');
        } else if (digit >= 'A' && digit <= 'F') {
          color |= (digit - 'A' + 10);
        } else if (digit >= 'a' && digit <= 'f') {
          color |= (digit - 'a' + 10);
        } else {
          uart_puts(UART0_BASE, "Invalid hex input.\r\n");
          color = -1;
          break;
        }
      }

      if (color >= 0) {
        color = ((color & 0xf80000) >> 8) | ((color & 0x00fc00) >> 5) | ((color & 0x0000f8) >> 3);

        for (int i = 0; i < 240 * 240; i++) {
          frameBuffer[i] = ~color;
        }

        // 设置要显示的区域为整个屏幕
        uart_puts(UART0_BASE, "Setting window...\r\n");
        st7789_SetWindow(0, 0, 239, 239);

        // 发送缓冲区数据
        uart_puts(UART0_BASE, "Sending buffer...\r\n");
        st7789_SendBuffer(frameBuffer, 240 * 240);
      }

      idx = 0;
    } else if (idx < sizeof(buffer) - 1) {
      buffer[idx++] = c;
    }
  }
}
