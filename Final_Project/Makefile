# this is a minimal makefile for demo purposes, keep it that way...
obj-m:=mqueue.o
mqueue-objs:=mq.o
V?=0
KDIR?=/lib/modules/$(shell uname -r)/build
# in an embedded system:
#KDIR:=[where the system maker gave me kernel headers+makefile or the kernel itself which has a makefile]
#ARCH:=arm
#CROSS_COMPILE:=[path+common prefix to where the toolchain is]
# You could also use W=2 and W=3 for more warnings but most kernel headers
# fail those...
W?=1
.PHONY: modules
modules:
	$(MAKE) -C $(KDIR) M=$(CURDIR) V=$(V) W=$(W) modules
.PHONY: clean
clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) V=$(V) clean
	rm -f *.stamp

user: user_read user_write read_write

user_read: user_read.o
	gcc user_read.o -o user_read -lpthread
user_write: user_write.o
	gcc user_write.o -o user_write -lpthread
read_write: read_write.o
	gcc read_write.o -o read_write -lpthread

user_read.o: user_read.c
	gcc -c user_read.c
user_write.o: user_write.c
	gcc -c user_write.c
read_write.o: read_write.c
	gcc -c read_write.c