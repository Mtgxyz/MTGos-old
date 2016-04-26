
all: mtgos user

mtgos:
	make -C kernel
	mv kernel/mtgos mtgos

user:
	make -C user
	mv user/*.elf .

clean:
	make -C kernel clean
	rm -rf mtgos

.PHONY: all mtgos user clean
