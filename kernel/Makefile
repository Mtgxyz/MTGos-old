include ../kernel.settings
SRCS = $(shell find hal/$(arch) -name '*.cpp' -o -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
LD = $(PREFIX)g++
LDFLAGS =  -nostdlib -nodefaultlibs -nostdlib -fno-builtin
ifeq ($(arch),x86)
	LDFLAGS += -m32 -T kernel.ld
endif
all: hal
	$(LD) $(LDFLAGS) -o mtgos $(OBJS)
hal:
	make -C hal
clean:
	make -C hal clean

.PHONY: all hal clean
