include ../kernel.settings
SRCS = $(shell find -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
CC = $(PREFIX)gcc
LD = $(PREFIX)ld
ASFLAGS = -m32
CFLAGS = -m32 -w -g -fno-stack-protector -nostdinc -I include -fpie
LDFLAGS = -melf_i386 -Ttest.ld
test.elf: $(OBJS)
		$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
		$(CC) $(CFLAGS) -c -o $@ $^

clean:
		rm $(OBJS)
.PHONY: clean
