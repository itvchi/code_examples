@Copies data from one point in memory to another, then printf copied data
.global _start

_start:
	ldr		r0, =instr	@Load input string address
	ldr		r1, =outstr	@Load output string address
	mov		r2, #5		@Set bytes to copy

loop:
	cmp		r2, #0
	beq		end
	sub		r2, #1		@Decrement number of bytes to copy
	ldrb	r3, [r0]	@Load byte
	strb	r3, [r1]	@Store byte
	add		r0, #1		@Increment input string address
	add		r1, #1		@Increment output string address
	b		loop

end:
	@No increment needed after loop exit
	mov		r0, #'\n'
	strb	r0, [r1]	@Store new line

	add		r1, #1		@Increment output string address
	mov		r0, #0		
	strb	r0, [r1]	@Store null termination 

	@Setup write
	mov		r0, #1		@ 1 = stdout
	ldr		r1, =outstr	@ load output string address
	mov		r2, #6		@ 6 = strlen
	mov		r7, #4		@ 4 = write
	svc		0

	@Setup exit
	mov		r0, #0	@ 0 = success exit code
	mov		r7, #1	@ 1 = exit
	svc		0

.data
instr:	.ascii	"INPUT"
outstr:	.fill	7, 1, 0
