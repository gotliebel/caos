.intel_syntax noprefix
.text
.global very_important_function
// rdi - N, rsi - A, rdx - B, rcx - R
very_important_function:
	mov r8, rcx
	xor r9, r9
	mov rcx, rdi
	vxorps ymm0, ymm0, ymm0
	Loopbegin:
		vxorps ymm1, ymm1, ymm1
		vmovaps ymm2, [rsi + r9]
		vmovaps ymm3, [rdx + r9]
		vaddps ymm2, ymm2, ymm3
		vmovaps [r8 + r9], ymm2
		vhaddps ymm2, ymm2, ymm1
		vhaddps ymm2, ymm2, ymm1
		vaddps ymm0, ymm0, ymm2
		add r9, 32
		sub rcx, 7
		loop Loopbegin
	vcvtsi2ss xmm1, xmm1, rdi
	xorps xmm4, xmm4
	vextractf128 xmm4, ymm0, 1
	addps xmm0, xmm4
	vdivss xmm0, xmm0, xmm1
	vcvtss2sd xmm0, xmm0, xmm0
	ret
