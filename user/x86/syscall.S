.global screenout_init
// void * screenout_init(int err);
screenout_init:
    mov 0x4(%esp), %eax
    push %eax
    xor %eax, %eax
    int $0x30
    pop %ecx
    ret

.global screenout_out
// void * screenout_out(void* handle, char *str);
screenout_out:
    push %ebx
    mov 0xC(%esp), %eax
    mov 0x8(%esp), %ebx
    push %eax
    xor %eax, %eax
    inc %eax
    int $0x30
    pop %ebx
    pop %ebx
    ret

.global screenout_clear
// void * screenout_clear(void* handle);
screenout_clear:
    push %ebx
    mov 0x8(%esp), %ebx
    xor %eax, %eax
    inc %eax
    inc %eax
    int $0x30
    pop %ebx
    ret

.global screenout_setcolor
// void * screenout_setcolor(void* handle, uint32_t BG, uint32_t FG)
screenout_setcolor:
    push %ebx
    mov 0x8(%esp), %ebx
    mov 0xC(%esp), %eax
    mov 0x10(%esp), %ecx
    push %ecx
    push %eax
    mov $3, %eax
    int $0x30
    pop %ebx
    pop %ebx
    pop %ebx
    ret

.global screenout_destroy
// void * screenout_destroy(void * handle)
screenout_destroy:
    push %ebx
    mov 0x8(%esp), %ebx
    xor %eax, %eax
    dec %ax
    int $0x30
    pop %ebx
    ret
