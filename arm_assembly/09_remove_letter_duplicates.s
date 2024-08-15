@ Remove letter duplicates from string
.global _start

.include "macros/write.s"

@Registers
@ r0: input string address
@ r1: output string address
@ r2: tmp read byte
@ r3: last read character

_start:
	ldr	r0, =instr		@Load input string address
	ldr	r1, =outstr		@Load output string address
	mov	r3, #0			@Preload r3 with 0

loop:
	ldrb r2, [r0], #1	@Read from r0 address to r2, then increment r0 address by one
	cmp	 r2, #0			@Check if character was null byte termination
	beq	 end			@If '\0', go to end label
	cmp  r2, r3			@Compare readed character with the previous one
	beq	 loop			@If equal, read next character
	strb r2, [r1], #1	@Store character to r1 address, then increment r1 address
	mov	 r3, r2			@Set last read character (in register r3)
	b	 loop

end:
	nullwrite	outstr

	@Setup exit syscall
	mov r0, #0	@Exit code
	mov r7, #1	@Exit syscall
	svc 0

.data
instr:	.ascii	"TTThis iiis ssstringgg wwwith soooome "
		.asciz	"duuuplicatesss iiinside ittt.\n"
outstr:	.fill	128, 1, 0	@Reserve 128 bytes, filled with 0
