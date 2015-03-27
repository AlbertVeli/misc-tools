#ifndef __XOR_H
#define __XOR_H

/* ~~=) All Rights Reversed (=~~ */

extern void xor_64(char *dst, char *s1, char *s2);
extern void xor_128(char *dst, char *s1, char *s2);
extern void otp_xor(char *dst, const char *s1, const char *s2, int len);
extern void c_xor(char *dst, const char *s, char c, int len);
extern void rep_xor(char *dst, const char *s, const char *k, int slen, int klen);
extern void otp_xnor(char *dst, const char *s1, const char *s2, int len);
extern void rep_xnor(char *dst, const char *s, const char *k, int slen, int klen);

/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */

#endif
