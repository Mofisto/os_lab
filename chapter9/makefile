#相关目标
all: build hd;
#all: ; $(info [${SRC_DIR}]) $(info [${OBJ_DIR}])  build

#echo Hello world


run:
	bochs -q -f bochsrc	 


.PHONY : all  build   run  clean  hd


#BUILD_DIR = build  
SRC_DIR = kernel
OBJ_DIR = build

#有点重复定义了，懒得改了，就这样用吧
#目录名千万不要有空格，不然报错会很奇怪
#https://stackoverflow.com/questions/13945091/make-error-of-mixed-implicit-and-normal-rules

#定义相关变量

ENTRY_POINT = 0x8400
AS = nasm
CC = gcc
LD = ld
LIB = -I lib/ -I lib/kernel/ -I lib/user/ -I kernel/ -I device/ -I thread/
ASFLAGS = -f elf32  -I boot/include/
ASFLAGS_Bin = -f bin  -I boot/include/
CFLAGS = -m32 -Wall $(LIB) -c -fno-builtin -W -Wstrict-prototypes \
         
		 #-Wall 禁用警告之类的
		 # -c 只编译不链接
		 #-fno-builtin 告知编译器不要采用内部函数，否则编译 gcc 提示和内部函数冲突
		 #-Wstrict-prototypes  要求函数声明中必须有参数类型，否则警告
		 #-Wmissing-prototypes  要求函数必须声明，否则警告
LDFLAGS = -m elf_i386 -Ttext $(ENTRY_POINT)  -e main -Map $(OBJ_DIR)/kernel.map



#SRC = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/init.o $(OBJ_DIR)/interrupt.o \
       $(OBJ_DIR)/timer.o $(OBJ_DIR)/kernel.o $(OBJ_DIR)/print.o \
       $(OBJ_DIR)/debug.o $(OBJ_DIR)/memory.o $(OBJ_DIR)/bitmap.o \
       $(OBJ_DIR)/string.o $(OBJ_DIR)/switch.o $(OBJ_DIR)/thread.o \
	   $(OBJ_DIR)/list.o 

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS)  $< -o  $@  

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c  #kernel 目录下的 C 文件
	$(CC) $(CFLAGS)  $< -o  $@

$(OBJ_DIR)/timer.o: device/timer.c  # device 下的 C 文件
	$(CC) $(CFLAGS)  $< -o  $@ 

$(OBJ_DIR)/bitmap.o: lib/kernel/bitmap.c  # device 下的 C 文件
	$(CC) $(CFLAGS)  $< -o  $@ 

$(OBJ_DIR)/list.o: lib/kernel/list.c
	$(CC) $(CFLAGS)  $< -o  $@ 

$(OBJ_DIR)/string.o: lib/string.c  # device 下的 C 文件
	$(CC) $(CFLAGS)  $< -o  $@ 

$(OBJ_DIR)/thread.o: thread/thread.c
	$(CC) $(CFLAGS)  $< -o  $@ 




#链接目标文件
$(OBJ_DIR)/kernel: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

#OBJS = $(patsubst  %.c,$(BUILD_DIR)/%.o,$(SRC))
#OBJS = $(patsubst  %.c,%.o,$(SRC))

# OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)  #这里的 %号很好用，将每个 .c 文件替换得到对应 .o 


# OBJS += $(BUILD_DIR)/kernel.o
# OBJS += $(BUILD_DIR)/print.o

#  %.o: %.c
# 	$(CC) $(CFLAGS)  $< -o  $(OBJ_DIR)/$@  


#这里处理实际上有点丑，但是没办法，我思考了下，只能选择这么写
#因为这些文件都分散在不同的文件夹
#第一条规则不适用

#汇编代码编译
$(OBJ_DIR)/kernel.o: kernel/kernel.s
	$(AS) $(ASFLAGS) $< -o $@
$(OBJ_DIR)/print.o: lib/kernel/print.s
	$(AS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/switch.o: thread/switch.s
	$(AS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/%.bin : boot/%.s
	$(AS) $(ASFLAGS_Bin) $< -o $@



build : $(OBJ_DIR)/kernel	#编写makefile 的一个细节，使用变量必须使用之前已经定义好的，否则变量为空

#制作image
hd: $(OBJ_DIR)/mbr.bin $(OBJ_DIR)/loader.bin 
	rm -rf hd10.img
	dd if=/dev/zero of=hd10.img bs=512 count=20480
	objcopy -I elf32-i386 -S -R ".eh_frame" -R ".comment" -O binary $(OBJ_DIR)/kernel $(OBJ_DIR)/kernel.bin
	dd if=$(OBJ_DIR)/mbr.bin of=hd10.img bs=512 count=1 conv=notrunc
	dd if=$(OBJ_DIR)/loader.bin of=hd10.img bs=512 count=3 seek=2 conv=notrunc
	dd if=$(OBJ_DIR)/kernel.bin of=hd10.img bs=512 count=38 seek=5 conv=notrunc

clean:
	cd $(OBJ_DIR) && rm -f ./*
