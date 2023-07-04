obj-m += my_timer.o
 
ifdef ARCH
	#You can update your Beaglebone path here.
	KDIR = /home/jc/BBB/tmp/lib/modules/5.10.65/build
else
	KDIR = /lib/modules/$(shell uname -r)/build
endif
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
