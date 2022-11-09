obj-m += hello_world.o
 
ifdef ARCH
	#You can update your Beaglebone path here.
	KDIR = /home/jc/BBB/tmp/lib/modules/5.10.65/build
else
	KDIR = /lib/modules/5.15.76-v7+/build
endif
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
