section .text

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -MAGIC_NUMBER

align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

global outb

outb:
	mov DX, [ESP + 4]
	mov AL, [ESP + 8]
	out DX, AL
	ret

global main

extern start_kernel

main:
	mov ESP, stack
	call start_kernel

.loop:
	hlt
	jmp .loop

section .bss

STACK_SIZE equ 10240 ; 10 KB

resb STACK_SIZE

stack: