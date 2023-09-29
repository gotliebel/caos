.intel_syntax noprefix
.section .text
.global A
.global very_important_function
very_important_function:
	mov rcx, rdi
	mov rbx, A
	loopbegin:
	mov rdi, offset input
	sub rsp, 8
	mov rsi, rsp
	mov r12, rcx
	mov r13, rbx
	mov r14, rsi
	call scanf
	mov rcx, r12
	mov rsi, r14
	mov rbx, r13
	mov rax, [rbx]
	mov r9, [rsi]
	imul r9
	mov rdx, 0
	mov r12, rcx
	mov r13, rbx
	mov rdi, offset output
	mov rsi, rax
	call printf
	mov rcx, r12
	mov rbx, r13
	add rsp, 8
	add rbx, 4
	loop loopbegin
	xor rax, rax
	ret

.data
input:
	.string "%i"
output:
	.string "%i\n"
