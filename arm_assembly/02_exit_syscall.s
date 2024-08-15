@A simple ARM assembly program that exits gracefully
.global _start

_start:
	mov r0, #3	@Pass exit code value to r0
	mov r7, #1	@Pass syscall number to r7 without the 0x900000 prefix
	svc	0		@Execute supervisor call
