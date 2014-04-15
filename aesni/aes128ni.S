###        -*- mode: asm; -*-      ###
###                                ###
###  ~~=) All Rights Reversed (=~~ ###
###                                ###
### ############################## ###

### (loosely based on the OpenSSL aes-ni code)

	.file "aes128ni.S"

### Include macros for FUN/FUN_E
#ifdef __APPLE__
	.include "macro_osx.inc"
#else
	.include "macro_linux.inc"
#endif

	.text

# SysV x86-64 calling convention.
#
# reg | function | saved by callee?
# ----|----------|------
# rax | retval   | no
# rbx | bp?      | yes
# rcx | arg 4    | no
# rdx | arg 3    | no
# rsp | stackp   | yes
# rbp | bp?      | yes
# rsi | arg 2    | no
# rdi | arg 1    | no
# r8  | arg 5    | no
# r9  | arg 6    | no
# r10 | temp     | no
# r11 | temp     | no
# r12 - r15      | yes
#
# xmm0-xmm1  | pass and return floating point args | no
# xmm2-xmm7  | pass floating point args            | no
# xmm8-xmm15 | temp                                | no
#
## Note. MS call conv requires xmm6/xmm7 to be restored by callee.
####


/* int aesni_128_set_decrypt_key(const unsigned char *userKey, AES128_KEY *key);
 *
 * userKey = 128 bits = 16 bytes
 *
 * Neither userKey nor key may be NULL. The program will *crash* if they are :)
 */
	FUN	aesni_128_set_decrypt_key
	subq	$8,%rsp
	call	_aesni_128_set_encrypt_key
	leaq	160(%rsi),%rdi		# rdi -> end of key schedule

	movups	(%rsi),%xmm0
	movups	(%rdi),%xmm1
	movups	%xmm0,(%rdi)
	movups	%xmm1,(%rsi)
	leaq	16(%rsi),%rsi
	leaq	-16(%rdi),%rdi

dec_key_inverse:
	movups	(%rsi),%xmm0
	movups	(%rdi),%xmm1
.byte	102,15,56,219,192		# aesimc xmm0, xmm1
.byte	102,15,56,219,201		# aesimc xmm1, xmm1
	leaq	16(%rsi),%rsi
	leaq	-16(%rdi),%rdi
	movups	%xmm0,16(%rdi)
	movups	%xmm1,-16(%rsi)
	cmpq	%rsi,%rdi
	ja	dec_key_inverse

	movups	(%rsi),%xmm0
.byte	102,15,56,219,192		# aesimc xmm0, xmm0
	movups	%xmm0,(%rdi)
	xorl	%eax,%eax
	addq	$8,%rsp
	FUN_E	aesni_128_set_decrypt_key


/* int aesni_128_set_encrypt_key(const unsigned char *userKey, AES128_KEY *key);
 *
 * userKey = 128 bits = 16 bytes
 */
	FUN	aesni_128_set_encrypt_key
	LAB _aesni_128_set_encrypt_key # Strange hack...
	subq	$8,%rsp

	movups	(%rdi),%xmm0	# pull first 128 bits of *userKey
	xorps	%xmm4,%xmm4	# low dword of xmm4 is assumed 0
	leaq	16(%rsi),%rax

	ALIGN_16
ten_rounds:
	movups	%xmm0,(%rsi)		# round 0
.byte	102,15,58,223,200,1		# round 1 (aeskeygenassist 0x1, xmm0, xmm1)
	call	key_expansion_128_cold
.byte	102,15,58,223,200,2		# round 2 (0x2)
	call	key_expansion_128
.byte	102,15,58,223,200,4		# round 3 (0x4)
	call	key_expansion_128
.byte	102,15,58,223,200,8		# round 4 (0x8)
	call	key_expansion_128
.byte	102,15,58,223,200,16		# round 5 (0x10)
	call	key_expansion_128
.byte	102,15,58,223,200,32		# round 6 (0x20)
	call	key_expansion_128
.byte	102,15,58,223,200,64		# round 7 (0x40)
	call	key_expansion_128
.byte	102,15,58,223,200,128		# round 8 (0x80)
	call	key_expansion_128
.byte	102,15,58,223,200,27		# round 9 (0x1b)
	call	key_expansion_128
.byte	102,15,58,223,200,54		# round 10 (0x36)
	call	key_expansion_128
	movups	%xmm0,(%rax)
	xorl	%eax,%eax		# return 0
	jmp	enc_key_ret

	ALIGN_16
enc_key_ret:
	addq	$8,%rsp
	FUN_E	aesni_128_set_encrypt_key

	ALIGN_16
key_expansion_128:
	movups	%xmm0,(%rax)
	leaq	16(%rax),%rax
key_expansion_128_cold:
	shufps	$16,%xmm0,%xmm4
	xorps	%xmm4,%xmm0
	shufps	$140,%xmm0,%xmm4
	xorps	%xmm4,%xmm0
	shufps	$255,%xmm1,%xmm1
	xorps	%xmm1,%xmm0
	ret


/* void aesni_128_encrypt(const unsigned char *msg, unsigned char *ct, const AES128_KEY *key);
 *
 * create key with aesni_128_set_encrypt_key() before calling this.
 */
	FUN	aesni_128_encrypt
	movups	(%rdi),%xmm2	# Move in to xmm2
	movl	$9,%eax		# hardcode to aes128 (9 rounds aesenc + 1 round aesenclast)
	movups	(%rdx),%xmm0	# rndkey0
	movups	16(%rdx),%xmm1	# rndkey1
	leaq	32(%rdx),%rdx
	xorps	%xmm0,%xmm2	# xor rndkey0, in
loop_enc1_1:
.byte	102,15,56,220,209	# aesenc xmm1, xmm2
	decl	%eax
	movups	(%rdx),%xmm1	# move next rndkey to xmm1
	leaq	16(%rdx),%rdx	# point rdx to next rndkey
	jnz	loop_enc1_1	# loop 9 times (eax 9 first time)
.byte	102,15,56,221,209	# aesenclast xmm1, xmm2
	movups	%xmm2,(%rsi)	# move final ciphertext to out
	FUN_E	aesni_128_encrypt


/* void aesni_128_decrypt(const unsigned char *ct, unsigned char *msg, const AES128_KEY *key);
 *
 * create key with aesni_128_set_decrypt_key() before calling this.
 */
	FUN	aesni_128_decrypt
	movups	(%rdi),%xmm2
	movl	$9,%eax		# hardcode to aes128
	movups	(%rdx),%xmm0
	movups	16(%rdx),%xmm1
	leaq	32(%rdx),%rdx
	xorps	%xmm0,%xmm2
loop_dec1_2:
.byte	102,15,56,222,209	# aesdec xmm1, xmm2
	decl	%eax
	movups	(%rdx),%xmm1
	leaq	16(%rdx),%rdx
	jnz	loop_dec1_2
.byte	102,15,56,223,209	# aesdeclast xmm1, xmm2
	movups	%xmm2,(%rsi)
	FUN_E	aesni_128_decrypt

	ENDFILE
