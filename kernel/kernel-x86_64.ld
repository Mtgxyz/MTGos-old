ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:x86-64)
SECTIONS
{
	. = 0x200000;
	kernel_start = .;
	.text : {
		*(multiboot)
		*(.text)
	}
	.data ALIGN(0x200000) : {
		start_ctors = .;
			KEEP(*( .init_array ));
			KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
			*(.ctors)
		end_ctors = .;
		start_dtors = .;
			*(.dtors)
		end_dtors = .;
		*(.data)
	}
	.rodata ALIGN(0x200000) : {
		*(.rodata)
	}
	.bss ALIGN(0x200000) : {
		*(.bss)
	}
	. = ALIGN(0x200000);
	kernel_end = .;
}
