all:
ifeq ("$(wildcard $(hd10.img))","")
	rm hd10.img
	#else
	#FILE_EXISTS = 0
endif
#这个语句对缩进非常敏感,尝试了很多次，终于实现了检测文件存在就删除的效果

	dd if=/dev/zero of=hd10.img bs=512 count=20480
	nasm -f bin -I ./boot/include/ -o ./out/loader.bin ./boot/loader.s
	nasm -f bin -I ./boot/include/ -o ./out/mbr.bin ./boot/mbr.s
	nasm -f elf32 -o ./out/print.o ./lib/kernel/print.s
	gcc -m32 -O3 -I lib/kernel/ -c -o ./out/main.o   ./kernel/main.c
	ld -m elf_i386 -Ttext 0x8400  -e main -o ./out/main ./out/main.o ./out/print.o
	objcopy -I elf32-i386 -S -R ".eh_frame" -R ".comment" -O binary ./out/main ./out/kernel.bin
	#ld main.o -Ttext 0xc0001500 -e main -o kernel.bin

	dd if=./out/mbr.bin of=hd10.img bs=512 count=1 conv=notrunc
	dd if=./out/loader.bin of=hd10.img bs=512 count=3 seek=2 conv=notrunc
	dd if=./out/kernel.bin of=hd10.img bs=512 count=7 seek=5 conv=notrunc
asm_call_c:
	gcc -c -m32 c_with_s_c.c -o c_with_s_c.o
	nasm -f elf32 c_with_s_s.s -o c_with_s_s.o
	ld -m elf_i386 c_with_s_c.o c_with_s_s.o -o c_with_s
run:
	bochs -f bochsrc
