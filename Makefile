ifeq ($(KERNELRELEASE),)  

KERNELDIR ?= /lib/modules/$(shell uname -r)/build 
PWD := $(shell pwd)  

.PHONY: build clean  

build:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules  

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm a.out
else  

$(info Building with KERNELRELEASE = ${KERNELRELEASE}) 
obj-m :=    custommouse.o  

endif
