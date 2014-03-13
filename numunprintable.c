/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <ctype.h>

#include "map.h"

int main(int argc, char *argv[])
{
   char *p;
   int buflen;
   int i;
   int sum = 0;

   if (argc != 2) {
      printf("Count number of unprintable characters in file\n");
      printf("Usage: %s <file>\n", argv[0]);
      return 1;
   }

   if (!init_map(argv[1])) {
      perror(argv[1]);
      return 1;
   }

   p = map;
   buflen = get_map_len();
   for (i = 0; i < buflen; i++) {
      if (!isprint(*p++)) {
         sum++;
      }
   }

   free_map();

   printf("%d\n", sum);

   return 0;
}


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */
