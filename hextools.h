#ifndef __HEXTOOLS_H
#define __HEXTOOLS_H

/* ~~=) All Rights Reversed (=~~ */

/* Define __func__ depending on gcc version */
#if __STDC_VERSION__ < 199901L
# if __GNUC__ >= 2
#  define __func__ __FUNCTION__
# else
#  define __func__ "<unknown>"
# endif
#endif

extern void b64_enc(const char *in, char *out, int len);
extern int b64_dec(const char *in, char *out, int len);
extern void hex2bin(char *hex, char *bin, int hexlen);
extern void bin2hex(char *bin, char *hex, int hexlen);
extern void out_raw(const char *buf, int len);
extern void out_hex(const char *buf, int len);

/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */

#endif
