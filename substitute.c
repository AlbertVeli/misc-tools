/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <string.h>

#include "map.h"

/* Default alphabet (rotate 3 steps, aka caesar) */
#define ALPHABET_LEN 26
int alphalen = ALPHABET_LEN;
char *default_clear_alpha = { "abcdefghijklmnopqrstuvwxyz" };
char *default_ciphr_alpha = { "defghijklmnopqrstuvwxyzabc" };

char alphabet_map[256];

void build_alphabet_map(char *clear, char *ciphr, int len)
{
   int i;

   for (i = 0; i < 256; i++) {
      alphabet_map[i] = i;      
   }

   for (i = 0; i < len; i++) {
      alphabet_map[(unsigned char)clear[i]] = ciphr[i];      
   }
}

int main(int argc, char *argv[])
{
   char *b1;
   int b1len;
   int i;
   char *p;
   char *a1 = NULL;
   char *a2 = NULL;

   if (argc == 4) {
      /* <file> <clear> <cipher>
       *   1       2       3
       */
      size_t len;
      a1 = argv[2];
      a2 = argv[3];
      len = strlen(a1);
      if (len != strlen(a2)) {
         printf("Cleartext and ciphertext alphabets needs to be the same size\n");
         return 1;
      }
      if (len < 1 || len > 256) {
         printf("alphabet length not in range 1-256\n");
         return 1;
      }
      alphalen = len;
   } else if (argc == 2) {
      /* Only filename given, use default alphabets */
      a1 = default_clear_alpha;
      a2 = default_ciphr_alpha;
   } else {
      printf("Usage: %s <file> [<clear alphabet> <cipher alphabet>]\n", argv[0]);
      return 1;
   }

   if (!init_map(argv[1])) {
      perror(argv[1]);
      return 1;
   }

   build_alphabet_map(a1, a2, alphalen);

   b1 = map;
   b1len = get_map_len();
   p = b1;

   for (i = 0; i < b1len; i++) {
      printf("%c", alphabet_map[(unsigned char)*p]);
      p++;
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
