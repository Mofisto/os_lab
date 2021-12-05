all:
ifeq ("$(wildcard $(hd10.img))","")
	rm hd10.img
	#else
	#FILE_EXISTS = 0
endif
#这个语句对缩进非常敏感,尝试了很多次，终于实现了检测文件存在就删除的效果

	nasm -f bin -I include -o loader.bin loader.S -l loader.list
	nasm -f bin -I include -o mbr.bin mbr.s -l mbr.list
	dd if=/dev/zero of=hd10.img bs=512 count=20480
	dd if=mbr.bin of=hd10.img bs=512 count=1 conv=notrunc
	dd if=loader.bin of=hd10.img bs=512 count=4 seek=2 conv=notrunc
run:
	bochs -f bochsrc
