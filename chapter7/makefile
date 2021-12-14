all:
ifeq ("$(wildcard $(hd10.img))","")
	rm hd10.img
	#else
	#FILE_EXISTS = 0
endif
#这个语句对缩进非常敏感,尝试了很多次，终于实现了检测文件存在就删除的效果

	dd if=/dev/zero of=hd10.img bs=512 count=20480
	nasm -f bin -I ./boot/include/ -o build/loader.bin boot/loader.s
	nasm -f bin -I ./boot/include/ -o build/mbr.bin boot/mbr.s

	nasm -f elf32 -o build/print.o lib/kernel/print.s
	nasm -f elf32 -o build/kernel.o kernel/kernel.s

	gcc -m32 -I lib/kernel/ -c -fno-builtin -o build/timer.o device/timer.c
	gcc -m32 -I lib/kernel/ -I lib/ -I kernel/ -c -fno-builtin -o build/main.o kernel/main.c
	#gcc -m32 -I lib/kernel/ -I lib/ -I kernel/ -c -fno-builtin -o build/init.o kernel/init.c
	gcc -m32 -I lib/kernel -I lib -I device -c -fno-builtin -o build/init.o kernel/init.c
	gcc -m32 -I lib/kernel/ -I lib/ -I kernel/ -c -fno-builtin -o build/interrupt.o kernel/interrupt.c
	
	ld -m elf_i386 -Ttext 0x8400  -e main -o build/main build/main.o  build/init.o  build/interrupt.o  build/kernel.o  build/timer.o	build/print.o

	objcopy -I elf32-i386 -S -R ".eh_frame" -R ".comment" -O binary ./build/main ./build/kernel.bin

	dd if=build/mbr.bin of=hd10.img bs=512 count=1 conv=notrunc
	dd if=build/loader.bin of=hd10.img bs=512 count=3 seek=2 conv=notrunc
	dd if=build/kernel.bin of=hd10.img bs=512 count=16 seek=5 conv=notrunc
clean:
	rm -rf  build/*
run:
	bochs -f bochsrc
