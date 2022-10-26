obj-m += ftrace_hook.o

ccflags-y := -I$(src)/include
ftrace_hook-y := src/handler.o src/module.o src/syscall.o user.o

PWD := $(CURDIR) 


overrided_syscalls_header := include/gen/overrided_syscalls.h
overrided_syscalls_table := overrided_syscalls.tbl  
gen_calls_hdr := ./scripts/gen_syscall_hdr.sh


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
table:
	$(gen_calls_hdr) $(overrided_syscalls_table) $(overrided_syscalls_header)
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 
install:
	sudo insmod ./ftrace_hook.ko
uninstall:
	sudo rmmod ftrace_hook
