all: x86
	#Currently only do X86
	mv x86/hal.o hal.o

x86:
	make -C x86

clean:
	rm -rf hal.o
	make -C x86 clean

.PHONY: all x86 clean
