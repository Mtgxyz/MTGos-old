include ../../kernel.settings
SRCS = $(shell find $(arch) -name '*.cpp' -o -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
all:
	make -C $(arch)
	ar rcs ../libhal.a $(OBJS)
clean:
	rm -rf hal.o
	make -C $(arch) clean

.PHONY: all clean
