BUILD_DIR = build
SRC_ROOT := $(shell realpath ../..)
VMLINUX_LDS = vmlinux.lds

include $(SRC_ROOT)/raspibm/Makefile.common


SUB_DIR = arch/arm64/kernel
CC_FILES = 
AS_FILES = head.S entry.S hyp-stub.S
include $(SRC_ROOT)/raspibm/Makefile.compile

SUB_DIR = arch/arm64/mm
AS_FILES = cache.S proc.S
include $(SRC_ROOT)/raspibm/Makefile.compile

SUB_DIR = arch/arm64/lib
AS_FILES = memset.S strncmp.S strlen.S
include $(SRC_ROOT)/raspibm/Makefile.compile

SUB_DIR = arch/arm64/kvm/hyp
AS_FILES = smccc_wa.S
include $(SRC_ROOT)/raspibm/Makefile.compile

BUILD_SUB_DIR = arch/arm64/kvm/hyp/nvhe
SUB_DIR = arch/arm64/kvm/hyp
AS_FILES = entry.S hyp-entry.S
$(subst /,_,$(BUILD_DIR)/$(BUILD_SUB_DIR))_CC_FLAGS = -D__KVM_NVHE_HYPERVISOR__
$(subst /,_,$(BUILD_DIR)/$(BUILD_SUB_DIR))_AS_FLAGS = -D__KVM_NVHE_HYPERVISOR__
$(subst /,_,$(BUILD_DIR)/$(BUILD_SUB_DIR))_POST_COMPILE = $(OBJCOPY) --prefix-symbols=__kvm_nvhe_ $@ $@
include $(SRC_ROOT)/raspibm/Makefile.compile

BUILD_SUB_DIR = arch/arm64/kvm/hyp/vhe
SUB_DIR = arch/arm64/kvm/hyp
AS_FILES = entry.S hyp-entry.S
$(subst /,_,$(BUILD_DIR)/$(BUILD_SUB_DIR))_CC_FLAGS = -D__KVM_VHE_HYPERVISOR__
$(subst /,_,$(BUILD_DIR)/$(BUILD_SUB_DIR))_AS_FLAGS = -D__KVM_VHE_HYPERVISOR__
include $(SRC_ROOT)/raspibm/Makefile.compile

SUB_DIR = mm
CC_FILES = init-mm.c
include $(SRC_ROOT)/raspibm/Makefile.compile

SUB_DIR = lib
CC_FILES = smp_processor_id.c
include $(SRC_ROOT)/raspibm/Makefile.compile

SUB_DIR = raspibm/lib
CC_FILES = gpio.c printf.c
AS_FILES = utils.S
include $(SRC_ROOT)/raspibm/Makefile.compile

SUB_DIR = raspibm/01_boot
CC_FILES = main.c setup.c stub.c
include $(SRC_ROOT)/raspibm/Makefile.compile

kernel: kernel8-rpi4.img

kernel8-rpi4.img: $(VMLINUX_LDS) $(OBJ_FILES)
	$(LD) $(LD_FLAGS) -T $(VMLINUX_LDS) -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(OBJCOPY) $(BUILD_DIR)/kernel8.elf -O binary $@
