include ../../kernel.settings
SRCS = $(shell find $(arch) -name '*.cpp' -o -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
all:
	$(MAKE) -C $(arch)
	ar rcs ../libhal.a $(OBJS)
clean:
	rm -rf hal.o
	$(MAKE) -C $(arch) clean

.PHONY: all clean
