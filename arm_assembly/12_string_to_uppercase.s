@Convert lowercase string characters to uppercase
.global	_start

.include "macros/write.s"

_start:
	nullwrite	str		@Print string before modifications
	
	ldr	r0, =str		@Load string address to r0
loop:
	ldrb r1, [r0], #1	@Load byte from string, then increment pointer
	cmp	 r1, #0			@Check if '\0'
	beq	 end
	cmp	 r1, #'z'
	bgt	 loop			@Process next character if greater than 'z'
	cmp	 r1, #'a'
	blt	 loop			@Process next character if lesser than 'a'
	@ if 'a' < r1 < 'z', then change
	sub	 r1, #32		@Change lowercase to uppercase
	strb r1, [r0, #-1]	@Save letter in previous byte (because pointer was incremented)
	b	 loop

end:
	nullwrite	str

	@Setup exit
	mov r0, #0	@Exit code
	mov	r7, #1	@Exit system call
	svc 0

.data
str:	.ascii	"--->this text was created "
		.asciz	"with only lower case letters (123_456)\n"
