/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"

int main(int argc, char *argv[])
{
   char *b1;
   int b1len;
   int i, b;
   char *p;

   if (argc != 2) {
      printf("Usage: %s <file>\n", argv[0]);
      printf("Will modularly add 256 single byte values to file\n");
      return 1;
   }

   if (!init_map(argv[1])) {
      perror(argv[1]);
      return 1;
   }

   b1 = map;
   b1len = get_map_len();

   for (b = 0; b < 256; b++) {
      p = b1;
      for (i = 0; i < b1len; i++) {
         printf("%c", *p + b);
         p++;
      }
   }

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
