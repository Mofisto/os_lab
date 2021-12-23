all:
ifeq ("$(wildcard $(hd10.img))","")
	rm hd10.img
	#else
	#FILE_EXISTS = 0
endif
	#生成list文件为了调试用
	#nasm -f bin -I include -o loader.bin loader.s -l loader.list
	#nasm -f bin -I include -o loader.bin loader.s -l loader.list
	nasm -f bin -I include -o mbr.bin mbr.s
	nasm -f bin -I include -o mbr.bin mbr.s
	dd if=/dev/zero of=hd10.img bs=512 count=20480
	dd if=mbr.bin of=hd10.img bs=512 count=1 conv=notrunc
	dd if=loader.bin of=hd10.img bs=512 count=1 seek=2 conv=notrunc
run:
	bochs -q -f bochsrc
