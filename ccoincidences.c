/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "hextools.h"
#include "xor.h"
#include "map.h"

float coincidences(unsigned char *buf1, unsigned char *buf2, int len)
{
   int i;
   int sum = 0;
   unsigned char *p1 = buf1;
   unsigned char *p2 = buf2;

   for (i = 0; i < len; i++) {
      if (*p1++ == *p2++) {
         sum++;
      }
   }

   return sum / (float)len;
}


int main(int argc, char *argv[])
{
   char *buf;
   int buflen;
   char *xorbuf = NULL;
   int i;

   if (argc != 2) {
      printf("Usage: %s <file>\n", argv[0]);
      return 1;
   }

   if (!init_map(argv[1])) {
      perror(argv[1]);
      return 1;
   }

   buf = map;
   buflen = get_map_len();

   xorbuf = malloc(buflen);
   if (!xorbuf) {
      fprintf(stderr, "Could not alloc %d bytes for xorbuf\n", buflen);
      free_map();
      return 1;
   }

   for (i = 0; i < buflen - 10 && i < 100; i++) {
      otp_xor(xorbuf, buf, &buf[i], buflen - i);
      printf("%d: %.2f%c\n", i,
             coincidences((unsigned char *)buf, (unsigned char *)&buf[i], buflen - i) * 100, '%');
   }

   free(xorbuf);
   free_map();

   return 0;
}


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */
