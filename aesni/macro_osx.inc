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
	.globl	_\fname
_\fname:
	.endm

	.macro FUN_E fname
	ret
	.endm

	.macro ENDFILE
	.subsections_via_symbols
	.endm

	.macro LAB labname
_\labname:
	.endm

	.macro ALIGN_16
	.p2align 4,,15
	.endm

	.macro RODATA
	.literal16
	.endm

	.macro D16 oname
	.p2align 4,,15
\oname:
	.endm

	.macro E16 oname
	.endm
