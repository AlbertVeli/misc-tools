/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hextools.h"
#include "xor.h"
#include "map.h"

int main(int argc, char *argv[])
{
   char *b1;
   int b1len;
   char *xorbuf = NULL;
   int i, b;
   char *p;

   if (argc != 2) {
      printf("Usage: %s <file>\n", argv[0]);
      printf("Will xor file with all 256 single byte values\n");
      return 1;
   }

   if (!init_map(argv[1])) {
      perror(argv[1]);
      return 1;
   }

   b1 = map;
   b1len = get_map_len();

   xorbuf = malloc(b1len);
   if (!xorbuf) {
      fprintf(stderr, "Could not alloc %d bytes for xorbuf\n", b1len);
      free_map();
      return 1;
   }

   for (b = 0; b < 256; b++) {
      memcpy(xorbuf, b1, b1len);
      p = xorbuf;
      for (i = 0; i < b1len; i++) {
         *p = *p ^ b;
         p++;
      }
      out_raw(xorbuf, b1len);
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
