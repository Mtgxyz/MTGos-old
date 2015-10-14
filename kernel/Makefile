include ../kernel.settings
SRCS = $(shell find -name '*.cpp' -o -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
LD = $(PREFIX)g++
LDFLAGS = -T kernel.ld -nostdlib -nodefaultlibs -m32 -nostdlib -fno-builtin
all: hal
	$(LD) $(LDFLAGS) -o mtgos $(OBJS)
hal:
	make -C hal
clean:
	make -C hal clean

.PHONY: all hal clean
