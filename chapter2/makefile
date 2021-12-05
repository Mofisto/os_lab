all:
	#nasm -f bin -o mbr.bin mbr.s
	nasm -f bin -o mbr.bin
	rm   hd10.img
	dd if=/dev/zero of=hd10.img bs=512 count=20480
	dd if=mbr.bin of=hd10.img bs=512 count=1 conv=notrunc
run:
	bochs -f bochsrc
