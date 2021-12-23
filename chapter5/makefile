all:
ifeq ("$(wildcard $(hd10.img))","")
	rm hd10.img
	#else
	#FILE_EXISTS = 0
endif
#这个语句对缩进非常敏感,尝试了很多次，终于实现了检测文件存在就删除的效果

	dd if=/dev/zero of=hd10.img bs=512 count=20480
	#nasm -f bin -I include -o loader.bin loader.s -l loader.list
	#nasm -f bin -I include -o mbr.bin mbr.s -l mbr.list
	nasm -f bin -I include -o loader.bin loader.s
	nasm -f bin -I include -o mbr.bin mbr.s
	gcc -c -m32 -o main.o main.c
	ld main.o -Ttext 0x8400  -m elf_i386 -e main -o main
	objcopy -I elf32-i386 -S -R ".eh_frame" -R ".comment" -O binary main kernel.bin
	#ld main.o -Ttext 0xc0001500 -e main -o kernel.bin

	dd if=mbr.bin of=hd10.img bs=512 count=1 conv=notrunc
	dd if=loader.bin of=hd10.img bs=512 count=3 seek=2 conv=notrunc
	dd if=kernel.bin of=hd10.img bs=512 count=200 seek=5 conv=notrunc
run:
	bochs -q -f bochsrc
