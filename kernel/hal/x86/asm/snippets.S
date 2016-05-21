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
	ret
.global loadIDT
//void _stdcall loadIDT(struct idtp* ptr);
loadIDT:
	mov 0x4(%esp), %eax
	lidt (%eax)
	ret
.global enterPaging
//void _stdcall enterPaging(uint32** pd);
enterPaging:
  mov 0x4(%esp), %eax
  mov %eax, %cr3
  mov %cr4, %eax
  or $0x10, %eax
  mov %eax, %cr4
  mov %cr0, %eax
  or $0x80000000, %eax
  mov %eax, %cr0
  mov (%esp), %eax
  ret

//Handle interrupts
.macro intr_stub nr
.global intr_stub_\nr
.align 16
intr_stub_\nr:
	pushl $0
	pushl $\nr
	jmp intr_common_handler
.endm
.macro intr_stub_error_code nr
.global intr_stub_\nr
.align 16
intr_stub_\nr:
	pushl $\nr
	jmp intr_common_handler
.endm
intr_stub 0
intr_stub 1
intr_stub 2
intr_stub 3
intr_stub 4
intr_stub 5
intr_stub 6
intr_stub 7
intr_stub_error_code 8
intr_stub 9
intr_stub_error_code 10
intr_stub_error_code 11
intr_stub_error_code 12
intr_stub_error_code 13
intr_stub_error_code 14
intr_stub 15
intr_stub 16
intr_stub_error_code 17
intr_stub 18
intr_stub 19
intr_stub 20
intr_stub 21
intr_stub 22
intr_stub 23
intr_stub 24
intr_stub 25
intr_stub 26
intr_stub 27
intr_stub 28
intr_stub 29
intr_stub 30
intr_stub 31
intr_stub 32
intr_stub 33
intr_stub 34
intr_stub 35
intr_stub 36
intr_stub 37
intr_stub 38
intr_stub 39
intr_stub 40
intr_stub 41
intr_stub 42
intr_stub 43
intr_stub 44
intr_stub 45
intr_stub 46
intr_stub 47
intr_stub 48
intr_stub 49
intr_stub 50
intr_stub 51
intr_stub 52
intr_stub 53
intr_stub 54
intr_stub 55
intr_stub 56
intr_stub 57
intr_stub 58
intr_stub 59
intr_stub 60
intr_stub 61
intr_stub 62
intr_stub 63
intr_stub 64
intr_stub 65
intr_stub 66
intr_stub 67
intr_stub 68
intr_stub 69
intr_stub 70
intr_stub 71
intr_stub 72
intr_stub 73
intr_stub 74
intr_stub 75
intr_stub 76
intr_stub 77
intr_stub 78
intr_stub 79
intr_stub 80
intr_stub 81
intr_stub 82
intr_stub 83
intr_stub 84
intr_stub 85
intr_stub 86
intr_stub 87
intr_stub 88
intr_stub 89
intr_stub 90
intr_stub 91
intr_stub 92
intr_stub 93
intr_stub 94
intr_stub 95
intr_stub 96
intr_stub 97
intr_stub 98
intr_stub 99
intr_stub 100
intr_stub 101
intr_stub 102
intr_stub 103
intr_stub 104
intr_stub 105
intr_stub 106
intr_stub 107
intr_stub 108
intr_stub 109
intr_stub 110
intr_stub 111
intr_stub 112
intr_stub 113
intr_stub 114
intr_stub 115
intr_stub 116
intr_stub 117
intr_stub 118
intr_stub 119
intr_stub 120
intr_stub 121
intr_stub 122
intr_stub 123
intr_stub 124
intr_stub 125
intr_stub 126
intr_stub 127
intr_stub 128
intr_stub 129
intr_stub 130
intr_stub 131
intr_stub 132
intr_stub 133
intr_stub 134
intr_stub 135
intr_stub 136
intr_stub 137
intr_stub 138
intr_stub 139
intr_stub 140
intr_stub 141
intr_stub 142
intr_stub 143
intr_stub 144
intr_stub 145
intr_stub 146
intr_stub 147
intr_stub 148
intr_stub 149
intr_stub 150
intr_stub 151
intr_stub 152
intr_stub 153
intr_stub 154
intr_stub 155
intr_stub 156
intr_stub 157
intr_stub 158
intr_stub 159
intr_stub 160
intr_stub 161
intr_stub 162
intr_stub 163
intr_stub 164
intr_stub 165
intr_stub 166
intr_stub 167
intr_stub 168
intr_stub 169
intr_stub 170
intr_stub 171
intr_stub 172
intr_stub 173
intr_stub 174
intr_stub 175
intr_stub 176
intr_stub 177
intr_stub 178
intr_stub 179
intr_stub 180
intr_stub 181
intr_stub 182
intr_stub 183
intr_stub 184
intr_stub 185
intr_stub 186
intr_stub 187
intr_stub 188
intr_stub 189
intr_stub 190
intr_stub 191
intr_stub 192
intr_stub 193
intr_stub 194
intr_stub 195
intr_stub 196
intr_stub 197
intr_stub 198
intr_stub 199
intr_stub 200
intr_stub 201
intr_stub 202
intr_stub 203
intr_stub 204
intr_stub 205
intr_stub 206
intr_stub 207
intr_stub 208
intr_stub 209
intr_stub 210
intr_stub 211
intr_stub 212
intr_stub 213
intr_stub 214
intr_stub 215
intr_stub 216
intr_stub 217
intr_stub 218
intr_stub 219
intr_stub 220
intr_stub 221
intr_stub 222
intr_stub 223
intr_stub 224
intr_stub 225
intr_stub 226
intr_stub 227
intr_stub 228
intr_stub 229
intr_stub 230
intr_stub 231
intr_stub 232
intr_stub 233
intr_stub 234
intr_stub 235
intr_stub 236
intr_stub 237
intr_stub 238
intr_stub 239
intr_stub 240
intr_stub 241
intr_stub 242
intr_stub 243
intr_stub 244
intr_stub 245
intr_stub 246
intr_stub 247
intr_stub 248
intr_stub 249
intr_stub 250
intr_stub 251
intr_stub 252
intr_stub 253
intr_stub 254
intr_stub 255

//This should cover everything.
.extern handleINT
intr_common_handler:
	push %ebp
	push %edi
	push %esi
	push %edx
	push %ecx
	push %ebx
	push %eax
	//Load kernel datasegs
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	push %esp
	call handleINT
	mov %eax, %esp
	//Load user datasegs
	mov $0x23, %ax
	mov %ax, %ds
	mov %ax, %es
	pop %eax
	pop %ebx
	pop %ecx
	pop %edx
	pop %esi
	pop %edi
	pop %ebp
	// Take error code and interrupt number from stack
	add $8, %esp
	// Exit interrupt
	iret
