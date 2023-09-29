    .intel_syntax noprefix

    .text
    .global very_important_function

    very_important_function:
    mov r14, rdi
    mov r13, 0
    .start_point1:
    vmovaps ymm0, [rsi + 4 * r13]
    vmovaps ymm1, [rdx + 4 * r13]
    vaddps ymm0, ymm1, ymm0
    vmovaps [rcx + 4 * r13], ymm0
    add r13, 8
    cmp r13, r14
    jae .close_point1
    jmp .start_point1
    .close_point1:
    mov r15, 0
    vxorps  ymm2, ymm2, ymm2
    .start_point2:
    vxorps  ymm3, ymm3, ymm3
    vmovaps ymm0, [rcx + 4 * r15]
    vhaddps ymm0, ymm0, ymm3
    vhaddps ymm0, ymm0, ymm3
    vaddps  ymm2, ymm2, ymm0
    add r15, 8
    cmp r15, r14
    jae .close_point2
    jmp .start_point2
    .close_point2:
    vcvtsi2ss xmm4, xmm4, rdi
    xorps xmm1, xmm1
    vextractf128 xmm1, ymm2, 1
    addps xmm2, xmm1
    vmovaps xmm0,  xmm2
    vcvtss2sd xmm0, xmm0, xmm0
    ret
