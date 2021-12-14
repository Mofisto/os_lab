ENTRY_POINT = 0x8400
AS = nasm
CC = gcc
LD = ld
LIB = -I lib/ -I lib/kernel/ -I lib/user/ -I kernel/ -I device/
ASFLAGS = -f elf32  -I boot/include/
ASFLAGS_Bin = -f bin  -I boot/include/
CFLAGS = -m32 -Wall $(LIB) -c -fno-builtin -W -Wstrict-prototypes \
         -Wmissing-prototypes 
		 #-Wall 禁用警告之类的
		 # -c 只编译不链接
		 #-fno-builtin 允许生成更快的代码
		 #-Wstrict-prototypes
LDFLAGS = -m elf_i386 -Ttext $(ENTRY_POINT)  -e main -Map $(BUILD_DIR)/kernel.map

BUILD_DIR = build
SRC_DIR = kernel
OBJ_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/init.o $(BUILD_DIR)/interrupt.o \
       $(BUILD_DIR)/timer.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/print.o \
       $(BUILD_DIR)/debug.o $(BUILD_DIR)/memory.o $(BUILD_DIR)/bitmap.o \
       $(BUILD_DIR)/string.o 

#OBJS = $(patsubst  %.c,$(BUILD_DIR)/%.o,$(SRC))
#OBJS = $(patsubst  %.c,%.o,$(SRC))

#OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)  #这里的 %号很好用，将每个 .c 文件替换得到对应 .o 


# OBJS += $(BUILD_DIR)/kernel.o
# OBJS += $(BUILD_DIR)/print.o

#  %.o: %.c
# 	$(CC) $(CFLAGS)  $< -o  $(OBJ_DIR)/$@  

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(CC) $(CFLAGS)  $< -o  $@  

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c  #kernel 目录下的 C 文件
	$(CC) $(CFLAGS)  $< -o  $@  

$(BUILD_DIR)/timer.o: device/timer.c  # device 下的 C 文件
	$(CC) $(CFLAGS)  $< -o  $@ 

$(BUILD_DIR)/bitmap.o: lib/kernel/bitmap.c  # device 下的 C 文件
	$(CC) $(CFLAGS)  $< -o  $@ 

$(BUILD_DIR)/string.o: lib/string.c  # device 下的 C 文件
	$(CC) $(CFLAGS)  $< -o  $@ 

#这里处理实际上有点丑，但是没办法，我思考了下，只能选择这么写


#汇编代码编译
$(BUILD_DIR)/kernel.o: kernel/kernel.s
	$(AS) $(ASFLAGS) $< -o $@
$(BUILD_DIR)/print.o: lib/kernel/print.s
	$(AS) $(ASFLAGS) $< -o $@


#链接目标文件
$(BUILD_DIR)/kernel: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

#制作image
hd: $(BUILD_DIR)/mbr.bin $(BUILD_DIR)/loader.bin 
	objcopy -I elf32-i386 -S -R ".eh_frame" -R ".comment" -O binary $(BUILD_DIR)/kernel $(BUILD_DIR)/kernel.bin
	dd if=$(BUILD_DIR)/mbr.bin of=hd10.img bs=512 count=1 conv=notrunc
	dd if=$(BUILD_DIR)/loader.bin of=hd10.img bs=512 count=3 seek=2 conv=notrunc
	dd if=$(BUILD_DIR)/kernel.bin of=hd10.img bs=512 count=27 seek=5 conv=notrunc

$(BUILD_DIR)/%.bin : boot/%.s
	$(AS) $(ASFLAGS_Bin) $< -o $@

clean:
	cd $(BUILD_DIR) && rm -f ./*

build: $(BUILD_DIR)/kernel	

run:
	bochs -f bochsrc	 

all: build hd;
#all: ; $(info [${SRC}]) $(info [${OBJS}]) build

#echo Hello world

.PHONY : all  build   run  clean  hd
