@Store preloaded values from register in memory and write memory content to stdout
.global _start

_start:
	@Begin register preload
	mov	r0, #'P'
	mov	r1, #'O'
	mov	r2, #'I'
	mov	r3, #'U'
	mov	r4, #'Y'
	mov	r5, #'T'
	mov	r6, #'R'
	mov	r7, #'E'
	mov	r8, #'W'
	mov	r9, #'Q'
	@End register preload

	ldr  r10, =string	@Load string address to r10
	strb r1, [r10] 		@Store 'O' at address from r10
	add  r10, #1		@Increment pointer to string
	strb r5, [r10]		@Store 'T'
	add  r10, #1
	strb r5, [r10]		@Store 'T'
	add  r10, #1
	strb r7, [r10]		@Store 'E'
	add  r10, #1
	strb r6, [r10]		@Store 'R'
	add  r10, #1
	mov  r0, #'\n'		@Store new line char immediate
	strb r0, [r10]		@Store '\n'
	add  r10, #1
	mov  r0, #0			@Null teminate string
	strb r0, [r10]		@Store '\0'

	@Write string to stdout
	mov	r0, #1		@Stdout fd
	ldr	r1, =string	@String address
	mov	r2, #6		@String length
	mov	r7, #4		@Write syscall
	svc	0

	@Exit from program
	mov	r0, #0	@Exit code (exit success)
	mov	r7, #1	@Exit syscall
	svc	0

.data
string:	.ascii	"          " @String that contains only spaces
