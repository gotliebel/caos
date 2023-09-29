    .intel_syntax noprefix
    .text
    .global very_important_function

    very_important_function:
    mov r8, 0
    mov r9, 1
    mov r10, 7
    mov r11, 32
    mov r12, rcx
    mov r13, r8
    mov rcx, rdi
    vxorps ymm0, ymm0, ymm0
    Begin:
    vmovaps ymm1, [rsi + r13]
    vmovaps ymm2, [rdx + r13]
    vxorps ymm3, ymm3, ymm3
    vaddps ymm1, ymm1, ymm2
    vmovaps [r12 + r13], ymm1
    vhaddps ymm1, ymm1, ymm3
    vhaddps ymm1, ymm1, ymm3
    vaddps ymm0, ymm0, ymm1
    sub rcx, r10
    add r13, 32
    loop Begin
    xorps xmm4, xmm4
    vcvtsi2ss xmm3, xmm3, rdi
    vextractf128 xmm4, ymm0, 1
    addps xmm0, xmm4
    vdivss xmm0, xmm0, xmm3
    vcvtss2sd xmm0, xmm0, xmm0
    ret


