FSH_OBJS := $(FSH_DIR)/src/handler.o \
            $(FSH_DIR)/src/fsh.o     \
            $(FSH_DIR)/src/syscall.o

FSH_INC_DIR := $(FSH_DIR)/include

obj-m += $(MODULE_NAME).o
ccflags-y := -I$(FSH_INC_DIR) -Wno-declaration-after-statement
$(MODULE_NAME)-objs :=  $(FSH_OBJS) $(FSH_CUSTOM_OBJS)
