obj-m += my_module.o

ccflags-y := -I$(src)/include -Wno-declaration-after-statement
my_module-y := src/handler.o src/fsh.o src/syscall.o user.o

PWD := $(CURDIR) 


overrided_syscalls_header := include/gen/overrided_syscalls.h
overrided_syscalls_table := overrided_syscalls.tbl  
gen_calls_hdr := ./scripts/gen_syscall_hdr.sh


all: table
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
table:
	$(gen_calls_hdr) $(overrided_syscalls_table) $(overrided_syscalls_header)
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 
install:
	sudo insmod ./my_module.ko
uninstall:
	sudo rmmod my_module
