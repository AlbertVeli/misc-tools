/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <string.h>
#include <string.h>

#include "hextools.h"

static char *table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* Return hex character corresponding to low four bits in nibble. */
static inline unsigned char hexnibble(unsigned char nibble)
{
   unsigned char hex = nibble & 0xf;

   if (hex > 9) {
      hex += 'a' - 10;
   } else {
      hex += '0';
   }

   return hex;
}

/* Return value (0-15) of hex character hexchar.
 * XXX: No error handling.
 */
static inline unsigned char binnibble(unsigned char hexchar)
{
   unsigned char val;

   if (hexchar >= '0' && hexchar <= '9') {
      val = hexchar - '0';
   } else if (hexchar >= 'a' && hexchar <= 'h') {
      val = 10 + hexchar - 'a';
   } else if (hexchar >= 'A' && hexchar <= 'H') {
      val = 10 + hexchar - 'A';
   } else {
      fprintf(stderr, "Warning (%s): invalid hex character %c\n", __func__, hexchar);
      val = 0;
   }

   return val;
}

static inline int b64idx(int c)
{
   char *p = strchr(table, c);

   if (!p) {
      p = table;
   }

   return p - table;
}

/* Decode base64 encoded string in.
 * Put result in out, which must be allocated beforehand.
 * Return length of decoded out string.
 */
int b64_dec(const char *in, char *out, int len)
{
   unsigned int q;
   int outlen = 0;

   if (len % 4) {
      return 0;
   }

   while (*in) {
      q = b64idx(*in++);
      q = q << 6 | b64idx(*in++);
      q = q << 6 | b64idx(*in++);
      q = q << 6 | b64idx(*in++);
      *out++ = (q >> 16) & 0xff;
      *out++ = (q >> 8) & 0xff;
      *out++ = q & 0xff;
      outlen += 3;
   }

   *out = 0;

   return outlen;
}

/* Base64 encode *in to *out, which must be able to hold
 * the whole encoded string (up to 4/3 times bigger than *in
 * + up to three bytes padding, to make length of *out a multiple of 4).
 */
void b64_enc(const char *in, char *out, int len)
{
   int i;
   unsigned char idx;
   unsigned char *ip;

   for(i = 0; i < len / 3; i++) {
      ip = (unsigned char *)&in[i * 3];
      idx = (*ip >> 2) & 0x3f;
      *out++ = table[idx];
      idx = ((*ip << 4) | (ip[1] >> 4)) & 0x3f;
      *out++ = table[idx];
      idx = ((ip[1] << 2) | (ip[2] >> 6)) & 0x3f;
      *out++ = table[idx];
      idx = ip[2] & 0x3f;
      *out++ = table[idx];
   }

   switch (len % 3) {

   case 0:
      break;

   case 1:
      ip = (unsigned char *)&in[i * 3];
      idx = (*ip >> 2) & 0x3f;
      *out++ = table[idx];
      idx = (*ip << 4) & 0x3f;
      *out++ = table[idx];
      *out++ = '=';
      *out++ = '=';
      break;

   case 2:
      ip = (unsigned char *)&in[i * 3];
      idx = (*ip >> 2) & 0x3f;
      *out++ = table[idx];
      idx = ((*ip << 4) | (ip[1] >> 4)) & 0x3f;
      *out++ = table[idx];
      idx = (ip[1] << 2) & 0x3f;
      *out++ = table[idx];
      *out++ = '=';
      break;

   default:
      break;
   }

   *out = 0;
}

/* Convert hex string *hex to binary string *bin.
 * Length of bin will be half of hex.
 * XXX: No error handling. Each byte in *hex must be
 *      in either %02x or %02X format.
 */
void hex2bin(char *hex, char *bin, int hexlen)
{
   char *bp = bin;
   char *hp = hex;
   int i;

   for (i = 0; i < hexlen / 2; i++) {
      *bp = (binnibble(*hp++) << 4);
      *bp += binnibble(*hp++);
      bp++;
   }
}

/* Convert *bin to hexstring. Hexlen is twice the length of *bin. */
void bin2hex(char *bin, char *hex, int hexlen)
{
   char *bp = bin;
   char *hp = hex;
   int i;

   for (i = 0; i < hexlen / 2; i++) {
      *hp++ = hexnibble(*bp >> 4);
      *hp++ = hexnibble(*bp & 0xf);
      bp++;
   }
}

/* Output len raw bytes from *buf to stdout */
void out_raw(const char *buf, int len)
{
   if (fwrite(buf, len, 1, stdout) != 1) {
      fprintf(stderr, "%s: fwrite failed\n", __func__);
   }
}

/* Output len bytes from *buf to stdout as hex */
void out_hex(const char *buf, int len)
{
   int i;

   for (i = 0; i < len; i++) {
      printf("%02x", buf[i]);
   }
}


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */
