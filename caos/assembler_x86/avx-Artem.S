.intel_syntax noprefix
.text
.global avx_sin

avx_sin:
mov r8, 1
mov r9, 19
mov r10, -1
mov r11, r8
mov r12, r10
mov rcx, r9
mov rax, r8
xorpd xmm1, xmm1
movapd xmm2, xmm0
addpd xmm1, xmm2
mulpd xmm0, xmm0
Begin:
add r11, r8
mul r11
add r11, r8
mul r11
mul r12
cvtsi2sd xmm4, rax
vdivsd xmm3, xmm0, xmm4
mulpd xmm2, xmm3
addpd xmm1, xmm2
mov rax, r8
loop Begin
movapd xmm0, xmm1
ret
