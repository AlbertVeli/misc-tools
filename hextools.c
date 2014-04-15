/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <string.h>
#include <string.h>
#include <ctype.h>

#include "hextools.h"

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
      printf("%02x", (unsigned char)*buf++);
   }
}

/* Output len bytes from *buf to stdout as canonical hex */
void out_canonical(const char *buf, int len)
{
   int i, j;

   for (i = 0; i < len; i++) {
      if (!(i & 0x0f)) {
         if (i >= 16) {
            buf = buf - 16;
            printf(" |");
            for (j = 0; j < 16; j++) {
               printf("%c", isprint(*buf) ? *buf : '.');
               buf++;
            }
            printf("|");
         }
         printf("\n%06x  ", i);
      } else if (!(i & 0x07)) {
         printf(" ");
      }
      printf("%02x ", (unsigned char)*buf++);
   }

   /* End of last row */
   if (len % 16) {
      /* Fill missing bytes with spaces */
      for (j = 0; j < 16 - (len % 16); j++) {
         printf("   ");
      }
      if (len % 16 < 8) {
         printf(" ");
      }

      /* Print printable */
      printf(" |");
      buf = buf - (len % 16);
      for (j = 0; j < len % 16; j++) {
         printf("%c", isprint(*buf) ? *buf : '.');
         buf++;
      }
      /* Fill missing bytes in printable section */
      for (j = 0; j < 16 - (len % 16); j++) {
         printf(" ");
      }
      printf("|\n");
   }
}


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */
