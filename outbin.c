/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <string.h>

#include "hextools.h"
#include "map.h"

int main(int argc, char *argv[])
{
   int i;
   char buf[1024*1024*4];
   int buflen;

   if (argc != 2) {
      printf("Usage: %s <hexfile>\n", argv[0]);
      printf("Hexfile should only contain hex, no offsets\n");
      printf("Use xxd -r instead if file contains address: hex\n");
      return 1;
   }

   if (!init_map(argv[1])) {
      perror(argv[1]);
      return 1;
   }

   buflen = strlen(map) / 2;
   hex2bin(map, buf, buflen * 2);

   for (i = 0; i < buflen; i++) {
      printf("%c", buf[i]);
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
