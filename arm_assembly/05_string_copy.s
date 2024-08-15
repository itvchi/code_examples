@Copies data from one point in memory to another, then printf copied data
.global _start

_start:
	ldr		r0, =instr	@Load input string address
	ldr		r1, =outstr	@Load output string address

	ldrb	r2, [r0]	@Load first byte
	strb	r2, [r1]	@Store first byte
	add		r0, #1		@Increment input string address
	add		r1, #1		@Increment output string address

	ldrb	r2, [r0]	@Load second byte
	strb	r2, [r1]	@Store second byte
	add		r0, #1
	add		r1, #1

	ldrb	r2, [r0]	@Load third byte
	strb	r2, [r1]	@Store third byte
	add		r0, #1
	add		r1, #1

	ldrb	r2, [r0]	@Load fourth byte
	strb	r2, [r1]	@Store fourth byte
	add		r0, #1
	add		r1, #1

	ldrb	r2, [r0]	@Load fifth byte
	strb	r2, [r1]	@Store fifth byte
	
	add		r1, #1
	mov		r0, #'\n'
	strb	r0, [r1]	@Store new line

	add		r1, #1
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
