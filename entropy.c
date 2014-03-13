/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "map.h"

float entropy(unsigned char *buf, int buflen)
{
   int i;
   int table[256];
   double sum;

   memset(table, 0, sizeof(table));

   /* Count occurances of each byte value */
   for (i = 0; i < buflen; i++) {
      table[buf[i]]++;
   }

   sum = 0;
   for (i = 0; i < 256; i++) {
      if (table[i] > 0) {
         double q = table[i] / (double)buflen;
         sum += q * log2(q);
      }
   }
   sum *= -1;

   return sum;
}


int main(int argc, char *argv[])
{
   char *buf;
   int buflen;

   if (argc != 2) {
      fprintf(stderr, "Usage: %s <file>\n", argv[0]);
      return 1;
   }

   if (!init_map(argv[1])) {
      perror(argv[1]);
      return 1;
   }

   buf = map;
   buflen = get_map_len();

   printf("%.2f bits/byte\n", entropy((unsigned char *)buf, buflen));

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
