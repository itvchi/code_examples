@Change letters in string to their complement
.global _start

.include "macros/write.s"

@Registers:
@ r0: string address
@ r1: tmp read byte
@ r2: complement letter

_start:
	nullwrite	str
	nullwrite	nl

	ldr		r0, =str	@Load string address 
loop:
	ldrb	r1, [r0]	@Load first byte
	cmp		r1, #0		@Hheck if '\0'
	beq		exit
switch:
	cmp 	r1, #'A'	@Compare with 'A'
	moveq	r2, #'T'	@Load complement letter if true
	beq		write		@Jump to write label
	cmp 	r1, #'T'	@Compare with 'T'
	moveq	r2, #'A'	@Load complement letter if true
	beq		write		@Jump to write label
	cmp 	r1, #'C'	@Compare with 'C'
	moveq	r2, #'G'	@Load complement letter if true
	beq		write		@Jump to write label
	cmp 	r1, #'G'	@Compare with 'G'
	moveq	r2, #'C'	@Load complement letter if true
	beq		write		@Jump to write label
	mov		r2, #'x'	@Default condition, load r2 with 'x'
write:
	strb	r2, [r0], #1	@Store r2 in r0 address, then increment r0
	beq		loop

exit:
	nullwrite	str

	@Print new line
	ldr	 r0, =str
	mov	 r1, #0x000A	@Store '\n' and '\0' in little endian
	strh r1, [r0]
	nullwrite	str

	@Setup exit syscall
	mov	r0, #0	@Exit code
	mov	r7, #1	@Exit syscall
	svc 0

.data
str:	.ascii	"GCATAGTCAATGCTAG"
		.asciz	"TATAGCTGAT"
nl:		.asciz	"\n"
