#include <define.h>

// UART寄存器偏移定义
#define UART_RBR 0x00 // 接收缓冲寄存器（读取）
#define UART_THR 0x00 // 发送保持寄存器（写入）
#define UART_DLL 0x00 // 波特率分频器低位
#define UART_DLH 0x04 // 波特率分频器高位
#define UART_IER 0x04 // 中断使能寄存器
#define UART_FCR 0x08 // FIFO控制寄存器
#define UART_LCR 0x0C // 线路控制寄存器
#define UART_MCR 0x10 // 调制解调器控制寄存器
#define UART_LSR 0x14 // 线路状态寄存器
#define UART_MSR 0x18 // 调制解调器状态寄存器
#define UART_SCR 0x1C // 刮擦寄存器

#define UART0_BASE 0xD4017000
#define UART1_BASE 0xD4017100
#define UART2_BASE 0xD4017200
#define UART3_BASE 0xD4017300
#define UART4_BASE 0xD4017400
#define UART5_BASE 0xD4017500
#define UART6_BASE 0xD4017600
#define UART7_BASE 0xD4017700
#define UART8_BASE 0xD4017800
#define UART9_BASE 0xD4017900

static const uint32_t UART_BASE[] = {UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE, UART4_BASE,
                                     UART5_BASE, UART6_BASE, UART7_BASE, UART8_BASE, UART9_BASE};

// LSR状态位定义
#define UART_LSR_DR   0x01 // 数据就绪
#define UART_LSR_THRE 0x20 // 发送保持寄存器空
#define UART_LSR_TEMT 0x40 // 发送器空

// LCR寄存器位定义
#define UART_LCR_DLAB 0x80 // 分频锁存访问位
#define UART_LCR_8N1  0x03 // 8数据位，无奇偶校验，1停止位

// FCR寄存器位定义
#define UART_FCR_ENABLE_FIFO 0x01 // 使能FIFO
#define UART_FCR_CLEAR_RCVR  0x02 // 清除接收FIFO
#define UART_FCR_CLEAR_XMIT  0x04 // 清除发送FIFO

// 读写寄存器的宏
#define UART_READ(base, offset)         (*(volatile uint32_t *)((base) + (offset)))
#define UART_WRITE(base, offset, value) (*(volatile uint32_t *)((base) + (offset)) = (value))

/**
 * 初始化UART
 * @param uart_base UART基址
 * @param baud_rate 波特率
 */
void uart_init(uint32_t uart_base, uint32_t baud_rate) {
  // 假设系统时钟为24MHz，计算分频值
  uint32_t divisor = 24000000 / (16 * baud_rate);

  // 设置DLAB位，允许访问分频器寄存器
  UART_WRITE(uart_base, UART_LCR, UART_LCR_DLAB);

  // 设置波特率
  UART_WRITE(uart_base, UART_DLL, divisor & 0xFF);
  UART_WRITE(uart_base, UART_DLH, (divisor >> 8) & 0xFF);

  // 清除DLAB位，设置数据格式为8N1（8数据位，无奇偶校验，1停止位）
  UART_WRITE(uart_base, UART_LCR, UART_LCR_8N1);

  // 使能FIFO，清除接收和发送FIFO
  UART_WRITE(uart_base, UART_FCR, UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);

  // 禁用所有中断
  UART_WRITE(uart_base, UART_IER, 0x00);
}

/**
 * 发送单个字符
 * @param uart_base UART基址
 * @param ch 要发送的字符
 */
void uart_putc(uint32_t uart_base, char ch) {
  // 等待发送FIFO为空
  while ((UART_READ(uart_base, UART_LSR) & UART_LSR_THRE) == 0)
    ;

  // 发送字符
  UART_WRITE(uart_base, UART_THR, ch);
}

/**
 * 发送字符串
 * @param uart_base UART基址
 * @param str 要发送的字符串
 */
void uart_puts(uint32_t uart_base, const char *str) {
  while (*str != '\0') {
    uart_putc(uart_base, *str++);
  }
}

/**
 * 接收单个字符（阻塞式）
 * @param uart_base UART基址
 * @return 接收到的字符
 */
char uart_getc(uint32_t uart_base) {
  while ((UART_READ(uart_base, UART_LSR) & UART_LSR_DR) == 0)
    ;

  return UART_READ(uart_base, UART_RBR);
}

/**
 * 检查是否有数据可读（非阻塞）
 * @param uart_base UART基址
 * @return 如果有数据可读返回true，否则返回false
 */
bool uart_data_available(uint32_t uart_base) {
  return (UART_READ(uart_base, UART_LSR) & UART_LSR_DR) != 0;
}

/**
 * 尝试接收单个字符（非阻塞式）
 * @param uart_base UART基址
 * @param ch 用于存储接收到字符的指针
 * @return 如果成功接收到字符返回true，否则返回false
 */
bool uart_try_getc(uint32_t uart_base, char *ch) {
  if (uart_data_available(uart_base)) {
    *ch = UART_READ(uart_base, UART_RBR);
    return true;
  }
  return false;
}
