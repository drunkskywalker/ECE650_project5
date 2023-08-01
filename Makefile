ifeq ($(KERNELRELEASE),)

TARGETS=sneaky_process sneaky_mod.ko

all: $(TARGETS)

KERNELDIR ?= /lib/modules/$(shell uname -r)/build 
PWD := $(shell pwd)  

.PHONY: build clean  

build: sneaky_mod.ko sneaky_process
sneaky_mod.ko:
	$(MAKE)  -C $(KERNELDIR) M=$(PWD) modules  
sneaky_process: sneaky_process.c
	$(CC) -o $@ $<
clean:
	rm -rf *.o *~ core .depend .*.cmd *.order *.symvers *.ko *.mod.c sneaky_process 
else  

$(info Building with KERNELRELEASE = ${KERNELRELEASE}) 
obj-m :=    sneaky_mod.o  

endif

