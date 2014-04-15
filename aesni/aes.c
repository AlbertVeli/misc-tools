/* ~~=) All Rights Reversed (=~~ */

#include "aes.h"
#include "../xor.h"

/* XXX: these are shared between threads if threading is enabled. */
static AES128_KEY key_d;
static AES128_KEY key_e;

/* key should be 128 bits (16 bytes) */
void aes_set_keys(const char *key)
{
   aesni_128_set_encrypt_key(key, &key_e);
   aesni_128_set_decrypt_key(key, &key_d);
}

/* ECB, encrypt each 16-byte block separately.
 * Pad msg to fill last 16-byte block before calling this.
 */
void aes_ecb_encrypt(const char *msg, char *ct, int len)
{
   int i;

   /* Loop through blocks */
   for (i = 0; i < len / AES_BLOCK_SIZE; i++) {
      /* Decrypt 1 AES_BLOCK_SIZE byte block (16 bytes) */
      aesni_128_encrypt(msg, ct, &key_d);
      ct += AES_BLOCK_SIZE;
      msg += AES_BLOCK_SIZE;
   }
}

/* ECB, decrypt each 16-byte block separately. */
void aes_ecb_decrypt(const char *ct, char *msg, int len)
{
   int i;

   /* Loop through blocks */
   for (i = 0; i < len / AES_BLOCK_SIZE; i++) {
      /* Decrypt 1 AES_BLOCK_SIZE byte block (16 bytes) */
      aesni_128_decrypt(ct, msg, &key_d);
      ct += AES_BLOCK_SIZE;
      msg += AES_BLOCK_SIZE;
   }
}

/* CBC decrypt (aes128). Remember to call aes_set_keys() first.
 * ct  - input ciphertext
 * msg - decoded message
 * iv  - 16 byte initialization vector
 * len - length (in bytes) of ct.
 *       Should be evenly divisible by AES_BLOCK_SIZE (16).
 *       Otherwise the incomplete last block is skipped.
 */
void aes_cbc_decrypt(const char *ct, char *msg, char *iv, int len)
{
   int i;

   /* Loop through blocks */
   for (i = 0; i < len / AES_BLOCK_SIZE; i++) {

      /* Decrypt 1 AES_BLOCK_SIZE byte block (16 bytes) */
      aesni_128_decrypt(ct, msg, &key_d);

      if (i == 0) {
         /* First block, xor with iv */
         xor_128(msg, msg, iv);
      } else {
         /* else, xor with prev ct */
         ct -= AES_BLOCK_SIZE;
         xor_128(msg, msg, (char *)ct);
         ct += AES_BLOCK_SIZE;
      }

      msg += AES_BLOCK_SIZE;
      ct += AES_BLOCK_SIZE;
   }
}

void aes_cbc_encrypt(char *msg, char *ct, char *iv, int len)
{
   int i;

   /* Loop through blocks */
   for (i = 0; i < len / AES_BLOCK_SIZE; i++) {

      if (i == 0) {
         /* First block, xor with iv */
         xor_128(msg, msg, iv);
      } else {
         /* else, xor with prev ct */
         ct -= AES_BLOCK_SIZE;
         xor_128(msg, msg, ct);
         ct += AES_BLOCK_SIZE;
      }

      /* Encrypt 1 AES_BLOCK_SIZE byte block (16 bytes) */
      aesni_128_encrypt(msg, ct, &key_e);
      msg += AES_BLOCK_SIZE;
      ct += AES_BLOCK_SIZE;
   }
}

/* Increase IV by 1, carry overflow bit to next byte */
static void inc_iv(unsigned char *iv)
{
   int i;
   for (i = 15; i >= 0; i--) {
      iv[i]++;
      if (iv[i] != 0) {
         return;
      }
   }
}

/* Decrypt (same as encrypt) in aes ctr mode */
void aes_ctr_decrypt(const char *ct, char *msg, char *iv, int len)
{
   int i;
   int left = len;
   int blocks = len / AES_BLOCK_SIZE;
   char tmp[16];
   if (len % AES_BLOCK_SIZE) {
      blocks++;
   }

   /* Loop through blocks */
   for (i = 0; i < blocks; i++) {

      /* Encrypt IV */
      aesni_128_encrypt(iv, tmp, &key_e);

      if (left >= 16) {
         xor_128(msg, (char *)ct, tmp);
         left -= 16;
         msg += AES_BLOCK_SIZE;
         ct += AES_BLOCK_SIZE;
         inc_iv((unsigned char *)iv);
      } else {
         otp_xor(msg, ct, tmp, left);
      }
   }
}

void aes_ctr_encrypt(const char *msg, char *ct, char *iv, int len)
{
   aes_ctr_decrypt(msg, ct, iv, len);
}

/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */
