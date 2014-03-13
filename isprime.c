/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <gmp.h>

int ishex(char *str)
{
   char *p = str;
   int hex = 0;
   while (*p) {
      if ((*p >= 'A' && *p <= 'F') ||
          (*p >= 'a' && *p <= 'f') ||
          (*p == 'x') || (*p == 'X')) {
         hex = 1;
      } else {
         if (*p < '0' || *p > '9') {
            fprintf(stderr, "Error: invalid character %c in string\n", *p);
            /* continue anyway? */
         }
      }
      p++;
   }

   return hex;
}

/* Decide if str is decimal or hex and load into N (must be initiated) */
void load_string(mpz_t Z, char *str)
{
   char *np = str;
   int base = 10;

   /* If hex, set base to 16 */
   if (ishex(np)) {
      base = 16;
   }

   /* remove heading 0x if present */
   if ((np[0] == '0') && ((np[1] == 'x') || (np[1] == 'X'))) {
      np += 2;
   }

   mpz_set_str(Z, np, base);
}

int main(int argc, char *argv[])
{
   mpz_t N;

   if (argc != 2) {
      fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
      return 1;
   }

   mpz_init(N);
   load_string(N, argv[1]);

   gmp_printf("%Zd is ", N);
   if (mpz_probab_prime_p(N, 25)) {
      printf("prime\n"); /* with a very high probability */
   } else {
      printf("not prime\n"); /* definitely not prime */
      return 1;
   }

   mpz_clear(N);

   return 0;
}


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */
