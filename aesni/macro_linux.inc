###        -*- mode: asm; -*-      ###
###                                ###
###  ~~=) All Rights Reversed (=~~ ###
###                                ###
### ############################## ###

### Abstract away differences between osx and linux.
### This code only works with clang -c on osx.
### On linux it should work with recent versions of gcc.

	.macro FUN fname
	.p2align 4,,15
	.globl	\fname
	.type	\fname, @function
\fname:
	.cfi_startproc
	.endm

	.macro FUN_E fname
	ret
	.cfi_endproc
	.size	\fname, .-\fname
	.endm

	.macro ENDFILE
	.section .note.GNU-stack,"",@progbits
	.endm

	.macro LAB labname
\labname:
	.endm

	.macro ALIGN_16
	.p2align 4,,15
	.endm

	.macro RODATA
	.section .rodata, "a"
	.endm

	.macro D16 oname
	.p2align 4,,15
\oname:
	.endm

	.macro E16 oname
	.type	\oname,@object
	.size	\oname, 16
	.endm
