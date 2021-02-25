obj-m += my_net_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

insert: all
	sudo insmod my_net_module.ko

remove: 
	sudo rmmod my_net_module.ko

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

