@Check executable with objdump and gdb
.global _start

_start:
	mov	r0, #0
	mov	r0, #32
	mov	r1, #64
	add	r2, r2, r0

.data
	.byte 0xDE
	.byte 0xAD
	.byte 0xBE
	.byte 0xEF
	.word 0xDEADBEEF
