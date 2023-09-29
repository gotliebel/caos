.intel_syntax noprefix
.text
.global avx_sin
//xmm0 - x
avx_sin:
	mov rcx, 19
	movapd xmm1, xmm0
	mov r12, 1
	mov rax, 1
	xorpd xmm2, xmm2
	addpd xmm2, xmm1
	mov r13, -1
	mulpd xmm0, xmm0
	Loopbegin:
		add r12, 1
		mul r12
		add r12, 1
		mul r12
		mul r13
		cvtsi2sd xmm3, rax
		vdivsd xmm4, xmm0, xmm3
		mulpd xmm1, xmm4
		addpd xmm2, xmm1
		mov rax, 1
		loop Loopbegin
	movapd xmm0, xmm2
	ret	
