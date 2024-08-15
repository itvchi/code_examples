@Export _start symbol for linker
.global _start

.text
@Entry point label
_start:
	add	r2, r3 @Add r2 to r3 and store in r2

@Data section of program
.data

@Store string data at address poited by label
hello:	.ascii	"Hello world"

@When executing, system throw "Illegal instruction" error
@It's caused by no exit syscall, so data after program are interpreted as instruction
