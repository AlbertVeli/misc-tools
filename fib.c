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
   mpz_t first, second, sum, count, stop;

   if (argc != 2) {
      fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
      return 1;
   }

   mpz_init(stop);
   load_string(stop, argv[1]);

   mpz_init(first);
   mpz_init(sum);

   mpz_init_set_ui(second, 1);
   mpz_init_set_ui(count, 1);

   while(mpz_cmp(stop, count)) {
      mpz_add(sum, first, second);
      mpz_set(first, second);
      mpz_set(second, sum);
      mpz_add_ui(count, count, 1);
   }

   mpz_out_str(stdout, 10, sum);

   mpz_clear(stop);
   mpz_clear(count);
   mpz_clear(sum);
   mpz_clear(second);
   mpz_clear(first);

   return 0;
}


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */
