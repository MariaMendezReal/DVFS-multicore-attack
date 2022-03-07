KERNEL_DIR=android_kernel/hikey-linaro/
obj-m += regul.o

all:
	make ARCH=arm64 CROSS_COMPILE=toolchain_aarch/bin/aarch64-linux-android- -C $(KERNEL_DIR)  M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
