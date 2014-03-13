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
   char *b2;
   int b1len;
   int b2len;
   char *xorbuf;

   if (argc != 3) {
      printf("Usage: %s <file1> <file2>\n", argv[0]);
      return 1;
   }

   if (!init_map(argv[1])) {
      perror(argv[1]);
      return 1;
   }

   if (!init_map2(argv[2])) {
      perror(argv[2]);
      return 1;
   }

   b1 = map;
   b1len = get_map_len();

   b2 = map2;
   b2len = get_map2_len();

   xorbuf = malloc(b1len);
   if (!xorbuf) {
      fprintf(stderr, "Could not alloc %d bytes for xorbuf\n", b1len);
      free_map();
      return 1;
   }

   if (b2len < b1len) {
      /* Repeating key */
      rep_xor(xorbuf, b1, b2, b1len, b2len);
   } else {
      /* One Time Pad */
      otp_xor(xorbuf, b1, b2, b1len);
   }
   out_raw(xorbuf, b1len);

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
