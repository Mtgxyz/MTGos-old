
all: mtgos user

mtgos:
	$(MAKE) -C kernel
	mv kernel/mtgos mtgos

user:
	$(MAKE) -C user
	mv user/*.elf .

clean:
	$(MAKE) -C kernel clean
	rm -rf mtgos
	find . -name '*.o' -delete

.PHONY: all mtgos user clean
