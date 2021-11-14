BUILD_DIR = build
SRC_ROOT := $(shell realpath ../..)
VMLINUX_LDS = vmlinux.lds

include $(SRC_ROOT)/raspibm/Makefile.common


SUB_DIR = raspibm/01_boot/arch/arm64/kernel
AS_FILES = head.S hyp-stub.S
CC_FILES = cpufeature.c setup.c
include $(SRC_ROOT)/raspibm/Makefile.compile

SUB_DIR = raspibm/01_boot/arch/arm64/mm
AS_FILES = cache.S proc.S
CC_FILES = mmu.c
include $(SRC_ROOT)/raspibm/Makefile.compile

SUB_DIR = raspibm/01_boot/init
CC_FILES = init_task.c main.c
include $(SRC_ROOT)/raspibm/Makefile.compile

SUB_DIR = raspibm/lib
AS_FILES = utils.S
CC_FILES = peripherals.c print.c
include $(SRC_ROOT)/raspibm/Makefile.compile

SUB_DIR = arch/arm64/lib
AS_FILES = memset.S
include $(SRC_ROOT)/raspibm/Makefile.compile

kernel: kernel8-rpi4.img

kernel8-rpi4.img: $(VMLINUX_LDS) $(OBJ_FILES)
	$(LD) $(LD_FLAGS) -T $(VMLINUX_LDS) -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(OBJCOPY) $(BUILD_DIR)/kernel8.elf -O binary $@
