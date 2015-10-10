
all: mtgos

mtgos:
	make -C kernel
	mv kernel/mtgos mtgos

clean:
	make -C kernel clean
	rm -rf mtgos

.PHONY: all mtgos clean
