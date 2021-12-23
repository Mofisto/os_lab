asm_call_c:c_with_s_c.c c_with_s_s.s
	gcc -c -m32 c_with_s_c.c -o c_with_s_c.o
	nasm -f elf32 c_with_s_s.s -o c_with_s_s.o
	ld -m elf_i386 c_with_s_c.o c_with_s_s.o -o c_with_s

syscall_write: syscall_write.s
	nasm -f elf32 -g -o syscall_write.o  syscall_write.s
	ld -m elf_i386 -o syscall_write  syscall_write.o
