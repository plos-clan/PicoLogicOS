ENTRY(_start)

SECTIONS {
  . = 0x40000000;

  .text : {
    *(.text .text.*)
  }

  . = ALIGN(8);

  .rodata : {
    *(.rodata .rodata.*)
  }

  . = ALIGN(8);

  .data : {
    *(.data .data.*)
  }

  . = ALIGN(8);

  .bss : {
    *(.bss .bss.*)
    *(COMMON)
  }

  . = ALIGN(8);
}
