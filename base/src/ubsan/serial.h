#pragma once

#define PORT 0x3f8 // COM1

static void klogc(char c) {
  waituntil(asm_in8(PORT + 5) & 0x20);
  asm_out8(PORT, c);
}

static void klogs(cstr s) {
  for (size_t i = 0; s[i] != '\0'; i++) {
    klogc(s[i]);
  }
}
