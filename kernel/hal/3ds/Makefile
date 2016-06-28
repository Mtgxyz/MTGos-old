include ../../../kernel.settings
ARM9SRCS = $(shell find arm9 -name '*.cpp' -o -name '*.[cS]')
ARM11SRCS = $(shell find arm11 -name '*.cpp' -o -name '*.[cS]')
ARM9OBJS = $(addsuffix .o,$(basename $(ARM9SRCS)))
ARM11OBJS = $(addsuffix .o,$(basename $(ARM11SRCS)))
ARM9FLAGS = -mcpu=arm946e-s -march=armv5te -mlittle-endian
ARM11FLAGS = -mcpu=mpcore -mlittle-endian

CPP = $(PREFIX)g++
CC = $(PREFIX)gcc
AR = $(PREFIX)ar
ASFLAGS =
CFLAGS += -Wall -fno-stack-protector -nostdinc -Ic_include/ -I../../kernel/c_include -ffreestanding -std=c11 -fno-builtin -Werror -nostdlib -g -fpie
CPPFLAGS += -Wall -fno-stack-protector -nostdinc -std=c++14 -Iinclude/ -Ic_include/ -I../../kernel/c_include -I../../kernel/include -fno-rtti -fno-exceptions -ffreestanding -fno-builtin -Werror -nostdlib  -fno-use-cxa-atexit -Wextra -Wno-unused -g -fno-pie -Wno-reorder

all: $(ARM9OBJS) $(ARM11OBJS)

arm9/%.o: arm9/%.cpp
	$(CPP) $(CPPFLAGS) $(ARM9FLAGS) -c -o $@ $^

arm9/%.o: arm9/%.c
	$(CC) $(CFLAGS) $(ARM9FLAGS) -c -o $@ $^

arm9/%.o: arm9/%.S
	$(CC) $(CFLAGS) $(ARM9FLAGS) -c -o $@ $^

arm11/%.o: arm11/%.cpp
	$(CPP) $(CPPFLAGS) $(ARM9FLAGS) -c -o $@ $^

arm11/%.o: arm11/%.c
	$(CC) $(CFLAGS) $(ARM9FLAGS) -c -o $@ $^

arm11/%.o: arm11/%.S
	$(CC) $(CFLAGS) $(ARM9FLAGS) -c -o $@ $^

clean:
