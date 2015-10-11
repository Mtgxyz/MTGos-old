SRCS = $(shell find -name '*.cpp' -o -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CPP = g++
CC = gcc
LD = ld
ASFLAGS = -m32
CFLAGS = -m32 -Wall -fno-stack-protector -nostdinc -Ic_include/ -ffreestanding -fbuiltin -march=native -std=c11 -fno-builtin
CPPFLAGS = -m32 -Wall -fno-stack-protector -nostdinc -std=c++14 -Iinclude/ -Ic_include/ -fno-rtti -fno-exceptions -ffreestanding -fbuiltin -march=native -fno-builtin
LDFLAGS = -r -melf_i386

include ../../../kernel.settings

hal.o: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: $.S
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(OBJS)

.PHONY: clean
