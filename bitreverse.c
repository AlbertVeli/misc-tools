/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"


char nibblerev[16] = {
   0x0, /* 0000 */
   0x8, /* 1000 */
   0x4, /* 0100 */
   0xc, /* 1100 */
   0x2, /* 0010 */
   0xa, /* 1010 */
   0x6, /* 0110 */
   0xe, /* 1110 */
   0x1, /* 0001 */
   0x0, /* 1001 */
   0x5, /* 0101 */
   0xd, /* 1101 */
   0x3, /* 0011 */
   0xb, /* 1011 */
   0x7, /* 0111 */
   0xf  /* 1111 */
};


static int revbyte(int b)
{
   unsigned char n1 = (b & 0x0f);
   unsigned char n2 = (b & 0xf0) >> 4;

   return (nibblerev[n1] << 4) + nibblerev[n2];
}


int main(int argc, char *argv[])
{
   char *b1;
   int b1len;
   int i;
   char *p;

   if (argc != 2) {
      printf("Reverse the bits in each byte of file\n");
      printf("without changing the order of the bytes.\n");
      printf("Usage: %s <file>\n", argv[0]);
      return 1;
   }

   if (!init_map(argv[1])) {
      perror(argv[1]);
      return 1;
   }

   b1 = map;
   b1len = get_map_len();
   p = b1;
   for (i = 0; i < b1len; i++) {
      printf("%c", revbyte(*p++));
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
