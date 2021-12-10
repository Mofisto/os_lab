section .data
str: db "Hello,World!",0xa,0x00
str_len equ $-str

section .text
extern c_print 
global _start
_start:
	push str
	call c_print
	add esp,4
	mov eax,1
	int 0x80

global asm_print
asm_print:
	push ebp
	mov ebp,esp
    mov eax,4
	mov ebx,1
	mov ecx,[ebp+8]
	mov edx,[ebp+12]
	int 0x80
    pop ebp
	ret
