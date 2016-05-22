ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)
SECTIONS
{
  . = 0x131000;
  .text : {
    *(.text)
  }
  .data ALIGN(4096) : {
		start_ctors = .;
			KEEP(*( .init_array ));
			KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
			*(.ctors)
		end_ctors = .;
		start_dtors = .;
			*(.dtors)
		end_dtors = .;
		*(.data)
    *(.got)
	}
	.rodata ALIGN(4096) : {
		*(.rodata)
	}
	.bss ALIGN(4096) : {
		*(.bss)
	}
	. = ALIGN(4096);
}
