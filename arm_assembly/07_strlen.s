@Print string on stdio, but automatically calculate string length
.global	_start

_start:
	@Setup write
	mov	r0, #1		@Stdout fd
	ldr	r1, =str	@Load string address
	@r2 will be load with calculated strlen
	mov	r7, #4		@Write syscall

	mov 	r2, #0		@Number of string characters
	mov 	r3, #0		@Null termination byte
	ldr 	r4, =str	@Load string address
loop:
	ldrb	r5, [r4]	@Load byte from string
	add		r4, #1		@Increment r4 pointer by one
	cmp 	r3, r5		@Compare string byte with '\0'
	beq		end
	add		r2, #1		@Increment strlen	
	b		loop

end:	@r2 contains strlen
	svc 0

	@Setup exit	
	mov r0, #0	@Exit code (success)
	mov r7, #1	@Exit syscall
	svc 0

.data
str:	.ascii	"Hello world!\n\0" @Null terminated string to print
