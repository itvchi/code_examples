@Print hello world string using macro for write operation
.global _start

.include "macros/write.s"

_start:
	@Write hello world string
	nullwrite	hello

	@Setup exit syscall
	mov	r0, #0	@Exit code
	mov	r7, #1	@Exit syscall
	svc	0

.data
hello:	.asciz	"Hello World!\n"	@Store null terminated string
@up - equivalent of .ascii "Hello World!\n\0"
