.section .text
.global _a9vectors_begin
.global _a9vectors_end
.extern _start
_a9vectors_begin:
  //b start
  b data_abort
  b fiq
  b irq
  b prefetch_abort
  b _svc
  b udi
start:
  b =_start
.extern handleINT9
data_abort:
  sub lr, #8
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #0
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT9
fiq:
  sub lr, #4
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #1
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT9
irq:
  sub lr, #4
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #2
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT9
prefetch_abort:
  sub lr, #4
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #3
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT9
_svc:
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #4
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT9
udi:
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #5
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT9
_a9vectors_end:
