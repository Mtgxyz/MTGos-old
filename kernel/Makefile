include ../kernel.settings
SRCS = $(shell find hal/$(arch) -name '*.cpp' -o -name '*.[cS]')
KERNSRCS = $(shell find kernel -name '*.cpp' -o -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
OBJS += $(addsuffix .o,$(basename $(KERNSRCS)))
LD = $(PREFIX)g++
LDFLAGS =  -nostdlib -nodefaultlibs -nostdlib -fno-builtin $(ARCHFLAGS) -T kernel-$(arch).ld -z max-page-size=0x1000 -lgcc

all: hal kernel
	$(LD) $(LDFLAGS) -o mtgos $(OBJS)
hal:
	make -C hal
kernel:
	make -C kernel
clean:
	make -C hal clean
	make -C kernel clean

.PHONY: all hal kernel clean
