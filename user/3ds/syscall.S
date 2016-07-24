.global screenout_init
// void * screenout_init(int err);
screenout_init:
    stmdb sp!, {r0} //r0 is err
    mov r0, #0
    svc #0 //Only one svc
    sub sp, #4
    bx lr

.global screenout_out
// void * screenout_out(void* handle, char *str);
screenout_out:
    stmdb sp!, {r1} // R1 is str
    mov r1, r0 //R0 is handle
    mov r0, #1
    svc #0
    add sp, #4
    bx lr

.global screenout_clear
// void * screenout_clear(void* handle);
screenout_clear:
    mov r1, r0
    mov r0, #2
    svc #0
    bx lr

.global screenout_setcolor
// void * screenout_setcolor(void* handle, uint32_t BG, uint32_t FG)
screenout_setcolor:
    stmdb sp!, {r1, r2}
    mov r1, r0
    mov r0, #3
    svc #0
    add sp, #8
    bx lr

.global screenout_destroy
// void * screenout_destroy(void * handle)
screenout_destroy:
    mov r1, r0
    mov r0, #0x10000
    sub r0, #1
    svc #0
    bx lr
