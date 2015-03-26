/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>

#include "map.h"

/* Edit cipher_alpha for different substitution ciphers.
 * For instance this string: lzzd://dsazorkf.qeg/1qDNnm3B
 * might lead to this ciphertext alphabet:
 * char *cipherf_alpha = { "srqponmlkjihgfedcbazyxwvut" };
 *
 * TODO: Read alphabets as cmdline arguments.
 */
#define ALPHABET_LEN 26
char *clear_alpha = { "abcdefghijklmnopqrstuvwxyz" };
char *ciphr_alpha = { "defghijklmnopqrstuvwxyzabc" };

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

   if (argc != 2) {
      printf("Usage: %s <file>\n", argv[0]);
      return 1;
   }

   if (!init_map(argv[1])) {
      perror(argv[1]);
      return 1;
   }

   build_alphabet_map(clear_alpha, ciphr_alpha, ALPHABET_LEN);

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
