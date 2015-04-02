/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <gmp.h>

#include "gmptools.h"


int main(int argc, char *argv[])
{
   mpz_t N;

   if (argc != 2) {
      fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
      return 1;
   }

   mpz_init(N);
   load_gmp_string(N, argv[1]);

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
