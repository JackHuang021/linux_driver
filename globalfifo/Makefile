KERNEL_DIR := /home/jack/Documents/phytium/e2000/linux-kernel
CURRENT_PATH := $(shell pwd)
obj-m := globalfifo.o

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNEL_DIR) M=$(CURRENT_PATH) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(CURRENT_PATH) clean
