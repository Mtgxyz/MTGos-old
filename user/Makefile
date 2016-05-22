include ../kernel.settings
SRCS = $(shell find -name '*.cpp')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
AS = $(PREFIX)gcc
CPP = $(PREFIX)g++
LD = $(PREFIX)ld
ASFLAGS = -m32
CPPFLAGS = -m32 -Wall -fno-stack-protector -nostdinc -std=c++14 -Iinclude/ -Ic_include/ -fno-rtti -fno-exceptions -ffreestanding -fno-builtin -Werror -nostdlib  -fno-use-cxa-atexit -Wextra -Wno-unused -g -fpie
LDFLAGS = -melf_i386 -Ttest.ld
test.elf: $(OBJS) $(arch)/syscall.o
		$(LD) $(LDFLAGS) -o $@ $^

%.o: %.cpp
		$(CPP) $(CPPFLAGS) -c -o $@ $^
$(arch)/syscall.o: $(arch)/syscall.S
	$(AS) $(ASFLAGS) -c -o $@ $^
clean:
		rm $(OBJS) $(arch)/syscall.o
.PHONY: clean
