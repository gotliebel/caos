	.text
	.global R
	.global calculate
calculate:
	adr x0, .Lexterns
	ldr x0, [x0]
	ldr x0, [x0]
	adr x1, .Lexterns
	ldr x1, [x1, 8]
	ldr x1, [x1]
	adr x2, .Lexterns
	ldr x2, [x2, 16]
	ldr x2, [x2]
	adr x3, .Lexterns
	ldr x3, [x3, 24]
	ldr x3, [x3]
	adr x4, R
	mul x0, x0, x1
	mul x2, x2, x3
	add x0, x0, x2
	str x0, [x4]
	ret
.section .data
R:
	.space 8
.Lexterns:
	.quad A
	.quad B
	.quad C
	.quad D
