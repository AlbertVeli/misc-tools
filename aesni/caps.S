###        -*- mode: asm; -*-      ###
###                                ###
###  ~~=) All Rights Reversed (=~~ ###
###                                ###
### ############################## ###

	.file "caps.S"

### Include macros for FUN/FUN_E
#ifdef __APPLE__
	.include "macro_osx.inc"
#else
	.include "macro_linux.inc"
#endif

	.text

	FUN	has_mmx
	push	%rbx
	mov	$1,%rax
	cpuid
	xor	%rax,%rax
	test	$0x800000,%rdx	# mmx = bit 23 of rdx
	setne	%al
	pop	%rbx
	FUN_E	has_mmx

	FUN	has_sse
	push	%rbx
	mov	$1,%rax
	cpuid
	xor	%rax,%rax
	test	$0x2000000,%rdx	# sse = bit 25 of rdx
	setne	%al
	pop	%rbx
	FUN_E	has_sse

	FUN 	has_sse2
	push	%rbx
	mov	$1,%rax
	cpuid
	xor	%rax,%rax
	test	$0x4000000,%rdx	# sse2 = bit 26 of rdx
	setne	%al
	pop	%rbx
	FUN_E 	has_sse2

	FUN	has_aes
        push    %rbx
        mov     $1,%rax
        cpuid
        xor     %rax,%rax
        test    $0x2000000,%rcx # aes = bit 25 of rcx
        setne   %al
        pop     %rbx
	FUN_E	has_aes

	FUN	has_pclmulqdq
        push    %rbx
        mov     $1,%rax
        cpuid
        xor     %rax,%rax
        test    $2,%rcx # aes = bit 1 of rcx
        setne   %al
        pop     %rbx
	FUN_E	has_pclmulqdq

	FUN	has_avx
	push	%rbx
	mov	$1,%eax
	cpuid
	xor	%eax,%eax	# eax <- 0
	and	$0x18000000,%ecx
	cmp	$0x18000000,%ecx
	jne	no_avx
	xor	%ecx,%ecx
	xgetbv
	mov	%eax,%ecx
	xor	%eax,%eax	# eax <- 0
	and	$6,%ecx
	cmp	$6,%ecx
	jne	no_avx
	mov	$1,%eax		# has avx, eax <- 1
no_avx:
	pop    %rbx
	FUN_E	has_avx

	ENDFILE
