.section .text
.global _a11vectors_begin
.global _a11vectors_end
.extern _start
_a11vectors_begin:
  //b start
  b data_abort
  b fiq
  b irq
  b prefetch_abort
  b _svc
  b udi
start:
//  b _start
.extern handleINT11
data_abort:
  sub lr, #8
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #0
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT11
fiq:
  sub lr, #4
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #1
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT11
irq:
  sub lr, #4
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #2
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT11
prefetch_abort:
  sub lr, #4
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #3
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT11
_svc:
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #4
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT11
udi:
  stmdb sp!, {r0-r12,lr}
  mov r0, sp
  mov r1, #5
  ldr r2, [pc, #4]
  blx r2
  ldmia sp!, {r0-r12, pc}^
.word handleINT11
_a11vectors_end:
.global initInterrupts
initInterrupts:
  MCR p15, 0, r0, c7, c7, 0
  bx lr
