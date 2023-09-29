.intel_syntax noprefix
.text
.global avx_sin

avx_sin:
.pre_calc:
 mov r8, 0
 mov r9, 21
 mov r10, 1
 mov r11,-1
.replace:
//in x2
 xorpd xmm2, xmm2
 movapd xmm2, xmm0
.first_arg:
 xorpd xmm1, xmm1
 movapd xmm1, xmm0
.calc_next_arg:
 mulpd xmm0, xmm0
.start_point:
 .calculate_diff:
   mov rax, 1
   add r10, 1
   mul r10
   add r10, 1
   mul r10
   mul r11
 .calculate_curr_rez:
   cvtsi2sd  xmm7, rax
   vdivsd   xmm5,  xmm0, xmm7
   mulpd    xmm1,  xmm5
   addpd    xmm2,  xmm1
   add r8, 1
   cmp r8, r9
   jae .close_point
     jmp .start_point
.close_point:
  movapd xmm0, xmm2
  ret
