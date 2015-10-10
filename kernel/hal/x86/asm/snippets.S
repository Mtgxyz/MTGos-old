.global loadGDT
//void _stdcall loadGDT(struct gdtp* ptr);
loadGDT:
	mov 0x4(%esp), %eax // Load argument
	lgdt (%eax)
	//GDT is loaded now
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ljmp $0x8, $.1
.1:
