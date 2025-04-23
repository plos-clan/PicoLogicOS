OUTPUT_FORMAT(elf64-x86-64)

ENTRY(_start)

PHDRS {
    limine_requests PT_LOAD FLAGS(4);
    text PT_LOAD FLAGS(5);
    rodata PT_LOAD FLAGS(4);
    thread PT_LOAD FLAGS(4);
    percpu PT_LOAD FLAGS(4);
    data PT_LOAD FLAGS(6);
    dmpt PT_LOAD FLAGS(6);
    stack PT_GNU_STACK FLAGS(6);
}

SECTIONS {
    . = 0xffffffff80000000;

    .limine_requests : ALIGN(4096) {
        KEEP(*(.limine_requests_start))
        KEEP(*(.limine_requests))
        KEEP(*(.limine_requests_end))
    } : limine_requests

    .text : ALIGN(4096) {
        *(.text .text.*)
    } : text

    .rodata : ALIGN(4096) {
        *(.rodata .rodata.*)
    } : rodata

    .data : ALIGN(4096) {
        *(.data .data.*)
        *(.bss .bss.*)
    } : data

    .dmpt : ALIGN(4096) {
        __plos_direct_map_page_table_start = .;
        . = . + 32K;
        __plos_direct_map_page_table_end = .;
    } : dmpt

    /DISCARD/ : {
        *(.eh_frame*)
        *(.note .note.*)
    }
}
