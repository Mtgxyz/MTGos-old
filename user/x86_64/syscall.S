.global screenout_init
// void * screenout_init(int err);
screenout_init:
  mov %rdi, %rax
  push %rax
  xor %rax, %rax
  int $0x30
  pop %rcx
  ret

.global screenout_out
// void * screenout_out(void* handle, char *str);
screenout_out:
  push %rbx
  mov %rsi, %rax
  mov %rdi, %rbx
  push %rax
  xor %rax, %rax
  inc %rax
  int $0x30
  pop %rbx
  pop %rbx
  ret

.global screenout_clear
// void * screenout_clear(void* handle);
screenout_clear:
  push %rbx
  mov %rdi, %rbx
  xor %rax, %rax
  inc %rax
  inc %rax
  int $0x30
  pop %rbx
  ret

.global screenout_setcolor
// void * screenout_setcolor(void* handle, uint32_t BG, uint32_t FG)
screenout_setcolor:
  push %rbx
  mov %rdi, %rbx
  mov %rsi, %rax
  mov %rdx, %rcx
  push %rcx
  push %rax
  mov $3, %rax
  int $0x30
  pop %rbx
  pop %rbx
  pop %rbx
  ret

.global screenout_destroy
// void * screenout_destroy(void * handle)
screenout_destroy:
  push %rbx
  mov %rdi, %rbx
  xor %rax, %rax
  dec %ax
  int $0x30
  pop %rbx
  ret
