	.section .text
	.global _start
_start:
	la sp, stack_top
	call main
1:
	j 1b
	
	.section .bss
	.space 4096
stack_top:
