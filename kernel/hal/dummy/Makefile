include ../../../kernel.settings
SRCS = $(shell find -name '*.cpp' -o -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CPP = $(PREFIX)g++
CC = $(PREFIX)gcc
ASFLAGS = 
CFLAGS = -Wall -fno-stack-protector -nostdinc -Ic_include/ -ffreestanding -march=native -std=c11 -fno-builtin -Werror -nostdlib -g
CPPFLAGS = -Wall -fno-stack-protector -nostdinc -std=c++14 -Iinclude/ -Ic_include/ -fno-rtti -fno-exceptions -ffreestanding -march=native -fno-builtin -Werror -nostdlib  -fno-use-cxa-atexit -Wextra -Wno-unused -g
LDFLAGS = -r 

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
