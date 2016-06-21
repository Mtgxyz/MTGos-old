include ../../kernel.settings
SRCS = $(shell find -name '*.cpp' -o -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
CPP = $(PREFIX)g++
CC = $(PREFIX)gcc
ASFLAGS = $(ARCHFLAGS)
CFLAGS += $(ARCHFLAGS) -Wall -fno-stack-protector -nostdinc -Ic_include/ -ffreestanding -std=c11 -fno-builtin -Werror -nostdlib -g -fpie
CPPFLAGS += $(ARCHFLAGS) -Wall -fno-stack-protector -nostdinc -std=c++14 -Iinclude/ -Ic_include/ -fno-rtti -fno-exceptions -ffreestanding -fno-builtin -Werror -nostdlib  -fno-use-cxa-atexit -Wextra -Wno-unused -g -fpie
all: $(OBJS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: $.S
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(OBJS)

.PHONY: clean all
