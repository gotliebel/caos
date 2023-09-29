	.text
	.file	"something.c"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$128, %rsp
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$.L.str, %edi
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	leaq	-8(%rbp), %rsi
	callq	__isoc99_scanf
	movl	-8(%rbp), %ecx
	movl	%ecx, %edx
	movl	%edx, %ecx
	addl	$1, %ecx
	movl	%ecx, %esi
	movq	%rsp, %rdi
	movq	%rdi, -16(%rbp)
	movq	%rdx, %rdi
	imulq	%rsi, %rdi
	leaq	15(,%rdi,8), %rdi
	andq	$-16, %rdi
	movq	%rsp, %r8
	subq	%rdi, %r8
	movq	%r8, %rsp
	movq	%rdx, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -36(%rbp)
	movq	%rsi, -104(%rbp)        # 8-byte Spill
	movq	%r8, -112(%rbp)         # 8-byte Spill
.LBB0_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
	movl	-36(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.LBB0_8
# %bb.2:                                #   in Loop: Header=BB0_1 Depth=1
	movl	$0, -40(%rbp)
.LBB0_3:                                #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	-40(%rbp), %eax
	movl	-8(%rbp), %ecx
	addl	$1, %ecx
	cmpl	%ecx, %eax
	jge	.LBB0_6
# %bb.4:                                #   in Loop: Header=BB0_3 Depth=2
	movslq	-36(%rbp), %rax
	movq	-104(%rbp), %rcx        # 8-byte Reload
	imulq	%rcx, %rax
	shlq	$3, %rax
	movq	-112(%rbp), %rdx        # 8-byte Reload
	addq	%rax, %rdx
	movslq	-40(%rbp), %rax
	shlq	$3, %rax
	addq	%rax, %rdx
	movabsq	$.L.str.1, %rdi
	movq	%rdx, %rsi
	movb	$0, %al
	callq	__isoc99_scanf
# %bb.5:                                #   in Loop: Header=BB0_3 Depth=2
	movl	-40(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -40(%rbp)
	jmp	.LBB0_3
.LBB0_6:                                #   in Loop: Header=BB0_1 Depth=1
	jmp	.LBB0_7
.LBB0_7:                                #   in Loop: Header=BB0_1 Depth=1
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	.LBB0_1
.LBB0_8:
	movl	$0, -44(%rbp)
.LBB0_9:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_11 Depth 2
                                        #       Child Loop BB0_13 Depth 3
	movl	-44(%rbp), %eax
	movl	-8(%rbp), %ecx
	subl	$1, %ecx
	cmpl	%ecx, %eax
	jge	.LBB0_20
# %bb.10:                               #   in Loop: Header=BB0_9 Depth=1
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -48(%rbp)
.LBB0_11:                               #   Parent Loop BB0_9 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB0_13 Depth 3
	movl	-48(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.LBB0_18
# %bb.12:                               #   in Loop: Header=BB0_11 Depth=2
	movslq	-48(%rbp), %rax
	movq	-104(%rbp), %rcx        # 8-byte Reload
	imulq	%rcx, %rax
	shlq	$3, %rax
	movq	-112(%rbp), %rdx        # 8-byte Reload
	addq	%rax, %rdx
	movslq	-44(%rbp), %rax
	movsd	(%rdx,%rax,8), %xmm0    # xmm0 = mem[0],zero
	movslq	-44(%rbp), %rax
	imulq	%rcx, %rax
	shlq	$3, %rax
	movq	-112(%rbp), %rdx        # 8-byte Reload
	addq	%rax, %rdx
	movslq	-44(%rbp), %rax
	divsd	(%rdx,%rax,8), %xmm0
	movsd	%xmm0, -56(%rbp)
	movl	$0, -60(%rbp)
.LBB0_13:                               #   Parent Loop BB0_9 Depth=1
                                        #     Parent Loop BB0_11 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	movl	-60(%rbp), %eax
	movl	-8(%rbp), %ecx
	addl	$1, %ecx
	cmpl	%ecx, %eax
	jge	.LBB0_16
# %bb.14:                               #   in Loop: Header=BB0_13 Depth=3
	movslq	-48(%rbp), %rax
	movq	-104(%rbp), %rcx        # 8-byte Reload
	imulq	%rcx, %rax
	shlq	$3, %rax
	movq	-112(%rbp), %rdx        # 8-byte Reload
	addq	%rax, %rdx
	movslq	-60(%rbp), %rax
	movsd	(%rdx,%rax,8), %xmm0    # xmm0 = mem[0],zero
	movsd	-56(%rbp), %xmm1        # xmm1 = mem[0],zero
	movslq	-44(%rbp), %rax
	imulq	%rcx, %rax
	shlq	$3, %rax
	movq	-112(%rbp), %rdx        # 8-byte Reload
	addq	%rax, %rdx
	movslq	-60(%rbp), %rax
	mulsd	(%rdx,%rax,8), %xmm1
	subsd	%xmm1, %xmm0
	movslq	-48(%rbp), %rax
	imulq	%rcx, %rax
	shlq	$3, %rax
	movq	-112(%rbp), %rdx        # 8-byte Reload
	addq	%rax, %rdx
	movslq	-60(%rbp), %rax
	movsd	%xmm0, (%rdx,%rax,8)
# %bb.15:                               #   in Loop: Header=BB0_13 Depth=3
	movl	-60(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -60(%rbp)
	jmp	.LBB0_13
.LBB0_16:                               #   in Loop: Header=BB0_11 Depth=2
	jmp	.LBB0_17
.LBB0_17:                               #   in Loop: Header=BB0_11 Depth=2
	movl	-48(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -48(%rbp)
	jmp	.LBB0_11
.LBB0_18:                               #   in Loop: Header=BB0_9 Depth=1
	jmp	.LBB0_19
.LBB0_19:                               #   in Loop: Header=BB0_9 Depth=1
	movl	-44(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -44(%rbp)
	jmp	.LBB0_9
.LBB0_20:
	movl	-8(%rbp), %eax
	movl	%eax, %ecx
	leaq	15(,%rcx,8), %rdx
	andq	$-16, %rdx
	movq	%rsp, %rsi
	subq	%rdx, %rsi
	movq	%rsi, %rsp
	movq	%rcx, -72(%rbp)
	movl	$0, -76(%rbp)
	movq	%rsi, -120(%rbp)        # 8-byte Spill
.LBB0_21:                               # =>This Inner Loop Header: Depth=1
	movl	-76(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.LBB0_24
# %bb.22:                               #   in Loop: Header=BB0_21 Depth=1
	movslq	-76(%rbp), %rax
	xorps	%xmm0, %xmm0
	movq	-120(%rbp), %rcx        # 8-byte Reload
	movsd	%xmm0, (%rcx,%rax,8)
# %bb.23:                               #   in Loop: Header=BB0_21 Depth=1
	movl	-76(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -76(%rbp)
	jmp	.LBB0_21
.LBB0_24:
	movl	-8(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -80(%rbp)
.LBB0_25:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_27 Depth 2
	cmpl	$0, -80(%rbp)
	jl	.LBB0_32
# %bb.26:                               #   in Loop: Header=BB0_25 Depth=1
	movslq	-80(%rbp), %rax
	movq	-104(%rbp), %rcx        # 8-byte Reload
	imulq	%rcx, %rax
	shlq	$3, %rax
	movq	-112(%rbp), %rdx        # 8-byte Reload
	addq	%rax, %rdx
	movslq	-8(%rbp), %rax
	movsd	(%rdx,%rax,8), %xmm0    # xmm0 = mem[0],zero
	movsd	%xmm0, -88(%rbp)
	movl	-8(%rbp), %esi
	subl	$1, %esi
	movl	%esi, -92(%rbp)
.LBB0_27:                               #   Parent Loop BB0_25 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	-92(%rbp), %eax
	cmpl	-80(%rbp), %eax
	jle	.LBB0_30
# %bb.28:                               #   in Loop: Header=BB0_27 Depth=2
	movsd	-88(%rbp), %xmm0        # xmm0 = mem[0],zero
	movslq	-80(%rbp), %rax
	movq	-104(%rbp), %rcx        # 8-byte Reload
	imulq	%rcx, %rax
	shlq	$3, %rax
	movq	-112(%rbp), %rdx        # 8-byte Reload
	addq	%rax, %rdx
	movslq	-92(%rbp), %rax
	movsd	(%rdx,%rax,8), %xmm1    # xmm1 = mem[0],zero
	movslq	-92(%rbp), %rax
	movq	-120(%rbp), %rdx        # 8-byte Reload
	mulsd	(%rdx,%rax,8), %xmm1
	subsd	%xmm1, %xmm0
	movsd	%xmm0, -88(%rbp)
# %bb.29:                               #   in Loop: Header=BB0_27 Depth=2
	movl	-92(%rbp), %eax
	addl	$-1, %eax
	movl	%eax, -92(%rbp)
	jmp	.LBB0_27
.LBB0_30:                               #   in Loop: Header=BB0_25 Depth=1
	movsd	-88(%rbp), %xmm0        # xmm0 = mem[0],zero
	movslq	-80(%rbp), %rax
	movq	-104(%rbp), %rcx        # 8-byte Reload
	imulq	%rcx, %rax
	shlq	$3, %rax
	movq	-112(%rbp), %rdx        # 8-byte Reload
	addq	%rax, %rdx
	movslq	-80(%rbp), %rax
	divsd	(%rdx,%rax,8), %xmm0
	movslq	-80(%rbp), %rax
	movq	-120(%rbp), %rdx        # 8-byte Reload
	movsd	%xmm0, (%rdx,%rax,8)
# %bb.31:                               #   in Loop: Header=BB0_25 Depth=1
	movl	-80(%rbp), %eax
	addl	$-1, %eax
	movl	%eax, -80(%rbp)
	jmp	.LBB0_25
.LBB0_32:
	movl	$0, -96(%rbp)
.LBB0_33:                               # =>This Inner Loop Header: Depth=1
	movl	-96(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.LBB0_36
# %bb.34:                               #   in Loop: Header=BB0_33 Depth=1
	movslq	-96(%rbp), %rax
	movq	-120(%rbp), %rcx        # 8-byte Reload
	movsd	(%rcx,%rax,8), %xmm0    # xmm0 = mem[0],zero
	movabsq	$.L.str.2, %rdi
	movb	$1, %al
	callq	printf
# %bb.35:                               #   in Loop: Header=BB0_33 Depth=1
	movl	-96(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -96(%rbp)
	jmp	.LBB0_33
.LBB0_36:
	movl	$0, -4(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rsp
	movl	-4(%rbp), %eax
	movq	%rbp, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%i"
	.size	.L.str, 3

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"%lf"
	.size	.L.str.1, 4

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"%lf "
	.size	.L.str.2, 5

	.ident	"clang version 10.0.0-4ubuntu1 "
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __isoc99_scanf
	.addrsig_sym printf
