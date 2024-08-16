@Outputs null terminated string

@Registers:
@ r0: output string address
@ r1: address pointer
@ r2: string byte value
@ r3: str length

@Labels (use local labels for multiple macro usage outside):
@ 1: loop entry point of string length calculation
@ 2: exit after finding null byte

.macro	nullwrite	outstr
	@ find length
	ldr  r0, =\outstr	@Load outstr address ('\'' beacuse of macro)
	mov  r1, r0			@Copy r0 to r1

1:
	ldrb r2, [r1]		@Load byte from r1 address
	cmp  r2, #0			@Check if it null byte
	beq  2f				@Go to label if null byte found
	add  r1, #1			@Increment pointer address
	b    1b				@Process loop again

2:
	sub	r3, r1, r0		@ strlen = r1 - r0

	@Setup write
	mov r0, #1			@Stdout fd
	ldr r1, =\outstr	
	mov r2, r3
	mov r7, #4			@Write syscall
	svc 0

.endm
