SRCS = $(shell find -name '*.cpp' -o -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
LD = g++
LDFLAGS = -T kernel.ld -nostdlib -nodefaultlibs
all: hal
	$(LD) $(LDFLAGS) -o mtgos $(OBJS)
hal:
	make -C hal
clean:
	make -C hal clean

.PHONY: all hal clean
