@Print "Hello world!" string to stdout

.global _start

_start:
	mov	r0, #1		@Move stdout file descriptor to r0
	ldr	r1, =hello	@Load address of buffer to r1
	ldr r2, =len	@Load len of message to r2
	mov	r7, #4		@Move write syscall number to r7
	svc	0			@Execute supervisor call

	mov	r0, #0	@Move exit code to r0
	mov	r7, #1	@Move exit syscall number to r7
	svc	0		@Execute supervisor call

.data
hello:	.ascii	"Hello world\n"
len = .-hello
