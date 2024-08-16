@Print "Hello world!" string to stdout
.global _start

_start:
	mov		r0, #1		@Move stdout file descriptor to r0
	ldr		r1, =hello	@Load addres of buffer to r1
	mov 	r2, #12		@Move buffer size to r2
	mov		r7, #4		@Move write syscall number to r7
	svc		0			@Execute supervisor call

	@Go to thumb mode
	ldr		r0, =#h_w_thumb		@Load address of instruction to jump
	add		r0, #1				@Increment addres by 1 (1 at LSB means switch to thumb mode)
	bx		r0					@Jump to address at r0

.thumb
h_w_thumb:
	mov		r0, #1		@Move stdout file descriptor to r0
	ldr		r1, =hello	@Load addres of buffer to r1
	mov 	r2, #12		@Move buffer size to r2
	mov		r7, #4		@Move write syscall number to r7
	svc		0			@Execute supervisor call

	@Go to arm mode
	ldr		r0, =#exit	@Load address of instruction to jump
	bx		r0			@Jump to address at r0

.arm
exit:
	mov		r7, #1	@Move exit syscall number to r7
	mov		r0, #0	@Move exit code to r0
	svc		0		@Execute supervisor call

.data
hello:	.ascii	"Hello world\n"
