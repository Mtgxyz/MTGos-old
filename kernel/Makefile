LD = ld
LDFLAGS = -melf_i386 -Tkernel.ld
all: hal
	$(LD) $(LDFLAGS) -o mtgos hal/hal.o
hal:
	make -C hal
clean:
	make -C hal clean

.PHONY: all hal clean
