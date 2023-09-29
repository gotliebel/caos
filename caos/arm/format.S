	.text
	.global main
main:
	sub sp, sp, 16
	str x30, [sp, 8]

	adr x0, type
	adr x1, first
	bl scanf
	adr x0, type
	adr x1, second
	bl scanf

	adr x1, first
	ldr x1, [x1]
	mov x2, x1
	adr x1, second
	ldr x1, [x1]
	mov x3, x1
	add x2, x2, x3
	mov x1, x2
	adr x0, type
	bl printf

	ldr x30, [sp, 8]
	add sp, sp, 16
	ret
.data
	type: .ascii "%i\0"
	first: .word 0
	second: .word 4

