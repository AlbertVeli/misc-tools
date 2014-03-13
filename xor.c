/* ~~=) All Rights Reversed (=~~ */

#include <stdint.h>

/* Fast xor of 64 bytes */
void xor_64(char *dst, char *s1, char *s2)
{
   uint64_t *dp = (uint64_t *)dst;
   uint64_t *p1 = (uint64_t *)s1;
   uint64_t *p2 = (uint64_t *)s2;

   *dp = *p1 ^ *p2;
}

/* One Time Pad. XOR s1 against s2, put result in dst. */
void otp_xor(char *dst, const char *s1, const char *s2, int len)
{
   uint64_t *dp = (uint64_t *)dst;
   uint64_t *p1 = (uint64_t *)s1;
   uint64_t *p2 = (uint64_t *)s2;
   int i;

   for (i = 0; i < (len >> 3); i++) {
      *dp++ = *p1++ ^ *p2++;
   }
   dst = (char *)dp;
   s1 = (char *)p1;
   s2 = (char *)p2;
   for (i = 0; i < len % 8; i++) {
      *dst++ = *s1++ ^ *s2++;
   }
}

/* XOR string s with single character c, put result in dst. */
void c_xor(char *dst, const char *s, char c, int len)
{
   int i;
   char buf[8];
   uint64_t *dp = (uint64_t *)dst;
   uint64_t *p1 = (uint64_t *)s;
   uint64_t *p2 = (uint64_t *)buf;

   for (i = 0; i < 8; i++) {
      buf[i] = c;
   }
   for (i = 0; i < (len >> 3); i++) {
      *dp++ = *p1++ ^ *p2++;
   }
   dst = (char *)dp;
   s = (char *)p1;
   for (i = 0; i < len % 8; i++) {
      *dst++ = *s++ ^ c;
   }
}

/* XOR string s with repeating key string k, put result in dst. */
void rep_xor(char *dst, const char *s, const char *k, int slen, int klen)
{
   int i;
   int left = slen;

   for (i = 0; i < slen; i +=klen) {
      if (left >= klen) {
         otp_xor(dst, s, k, klen);
         dst += klen;
         s += klen;
         left -= klen;
      } else {
         otp_xor(dst, s, k, left);
      }
   }
}


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */
