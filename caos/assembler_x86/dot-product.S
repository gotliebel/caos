.intel_syntax noprefix
.text
.global dot_product
//N - rdi, A - rsi, B - rdx
dot_product:
	mov rcx, rdi
	mov rbx, rcx
	mov r9, 0
	mov r10, 8
	mov r11, rdx
	mov r12, 0
	vcvtsi2ss xmm6, xmm6, r12
	mov rcx, 9
	mov rax, 32
	mul rdi
	mov r10, rax
	MakeZero:
		vmovups [rsi + r10], xmm6
		vmovups [r11 + r10], xmm6
        	add r10, 32
		loop MakeZero
	vxorps ymm3, ymm3, ymm3
	Loopbegin:
		vmovups ymm0, [rsi + r9]
		vmovups ymm1, [r11 + r9]
		vmulps ymm0, ymm0, ymm1
		add r9, 32
		vxorps ymm2, ymm2, ymm2
		vhaddps ymm0, ymm0, ymm2
		vhaddps ymm0, ymm0, ymm2
		vaddps ymm3, ymm3, ymm0
		add r12, 8
		cmp r12, rdi
		jl Loopbegin
	vextractf128 xmm5, ymm3, 1
	addps xmm3, xmm5
	movaps xmm0, xmm3
	ret
