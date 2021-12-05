;-------------	 loader和kernel   ----------

LOADER_BASE_ADDR equ 0x900
LOADER_STACK_TOP equ LOADER_BASE_ADDR 
LOADER_START_SECTOR equ 0x2



KERNEL_BIN_BASE_ADDR equ 0x70000
KERNEL_START_SECTOR equ 0x9
KERNEL_ENTRY_POINT equ 0xc0001500

;-------------   页表配置   ----------------
PAGE_DIR_TABLE_POS equ 0x100000

;--------------   gdt描述符属性  -------------
;------只是为了方便构建段描述符而定义的符号-------
DESC_G_4K   equ	  1_000_0000_0000_0000_0000_0000b ;G位为1时，段界限以4KB为单位
DESC_D_32   equ	   1_00_0000_0000_0000_0000_0000b ;D位为1，默认偏移地址或操作数大写
DESC_L	    equ	    0_0_0000_0000_0000_0000_0000b ;64位代码标记，此处标记为0便可。
DESC_AVL    equ	      0_0000_0000_0000_0000_0000b ;CPU不用此位，暂置为0  
DESC_LIMIT_CODE2  equ   1111_0000_0000_0000_0000b
DESC_LIMIT_DATA2  equ   DESC_LIMIT_CODE2
DESC_LIMIT_VIDEO2  equ   0000_000_0000_0000_0000b ;
DESC_P	    equ		        1_000_0000_0000_0000b ;P位为1，段存在
DESC_DPL_0  equ		   		 00_0_0000_0000_0000b ;DPL为0，段的特权级为 0
DESC_DPL_1  equ		         01_0_0000_0000_0000b ;DPL为1，段的特权级为 1
DESC_DPL_2  equ		         10_0_0000_0000_0000b ;DPL为2，段的特权级为 2
DESC_DPL_3  equ		         11_0_0000_0000_0000b ;DPL为3，段的特权级为 3
DESC_S_CODE equ		            1_0000_0000_0000b ;S 位为1，代码段或者数据段
DESC_S_DATA equ	                DESC_S_CODE
DESC_S_sys  equ		            0_0000_0000_0000b ;S 位为0，系统段
DESC_TYPE_CODE  equ	      		  1000_0000_0000b	;x=1,c=0,r=0,a=0 代码段是可执行的,非依从的,不可读的,已访问位a清0.  
DESC_TYPE_DATA  equ	              0010_0000_0000b	;x=0,e=0,w=1,a=0 数据段是不可执行的,向上扩展的,可读的，可写的,已访问位a清0.


;----构建 代码段、数据段、显存段的的描述符高4个字节----
DESC_CODE_HIGH4 equ (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_CODE2 + DESC_P + DESC_DPL_0 + DESC_S_CODE + DESC_TYPE_CODE + 0x00
DESC_DATA_HIGH4 equ (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_DATA2 + DESC_P + DESC_DPL_0 + DESC_S_DATA + DESC_TYPE_DATA + 0x00
DESC_VIDEO_HIGH4 equ (0x00 << 24) + DESC_G_4K + DESC_D_32 + DESC_L + DESC_AVL + DESC_LIMIT_VIDEO2 + DESC_P + DESC_DPL_0 + DESC_S_DATA + DESC_TYPE_DATA + 0x0b
;因为显存的起始地址是 0xb8000 ，所以显存段描述符的高4个字节最低8位，应该是 0x0b

;--------------   选择子属性  ---------------
RPL0  equ   00b
RPL1  equ   01b
RPL2  equ   10b
RPL3  equ   11b
TI_GDT	 equ   000b  ;TI位指示使用 GDT 还是 LDT 
TI_LDT	 equ   100b  ;TI位


;----------------   页表相关属性    --------------
PG_P  equ       1b
PG_RW_R	 equ   00b 
PG_RW_W	 equ   10b 
PG_US_S	 equ  000b 
PG_US_U	 equ  100b 


;-------------  program type 定义   --------------
PT_NULL equ 0