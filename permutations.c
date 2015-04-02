/* (k) ALL RIGHTS REVERSED - Reprint what you like */

#include <stdio.h>
#include <gmp.h>

#include "gmptools.h"

#define MAX 96

/* Uncomment to also print the prime factors */
//#define PRINT_FACTORS 1

/* For factorization */
unsigned long factors[MAX];
int n_fac = 0;

/* For combinations algorithm */
int i_left[MAX];
int i_right[MAX];
int maxk = 0;


static int get_factors(mpz_t N)
{
   mpz_t d, rem, tmp, r;
   int ret = 0;

   mpz_init_set_ui(d, 2);
   mpz_init_set(rem, N);
   mpz_init(tmp);
   mpz_init(r);

   /* Divide by 2 while even */
   while (mpz_even_p(rem) && (mpz_cmp_ui(rem, 1) > 0)) {
      mpz_cdiv_q(rem, rem, d);
      factors[n_fac++] = 2;
      if (n_fac == MAX) {
         fprintf(stderr, "Too many factors, quitting\n");
         ret = 1;
         goto out;
      }
   }

   while (mpz_cmp_ui(rem, 1) > 0) {
      mpz_nextprime(d, d);
      do {
         mpz_cdiv_qr(tmp, r, rem, d);
         if (mpz_cmp_ui(r, 0) == 0) {
            mpz_set(rem, tmp);
            if (n_fac < MAX) {
               factors[n_fac++] = mpz_get_ui(d);
            } else {
               fprintf(stderr, "Too many factors, quitting\n");
               ret = 1;
               goto out;
            }
         }
      } while (mpz_cmp_ui(r, 0) == 0);
   }

 out:

   mpz_clear(r);
   mpz_clear(tmp);
   mpz_clear(rem);
   mpz_clear(d);

   return ret;
}

/* Combination algorith based on an example from this page:
 * http://www.cs.utexas.edu/users/djimenez/utsa/cs3343/lecture25.html
 */
static void combinations(int start, int n, int k)
{
  int i;

  /* k here counts through positions in the maxk-element v.
   * if k > maxk, then the v is complete and we can use it.
   */
  if (k > maxk) {
    int suml = 0;
    int sumr = 0;

    /* Init right to all */
    for (i = 1; i <= n; i++) {
      i_right[i] = i;
    }

    for (i = 1; i <= maxk; i++) {
#ifdef PRINT_FACTORS
      printf("%ld ", factors[i_left[i] - 1]);
#endif
      if (suml == 0) {
	suml = factors[i_left[i] - 1];
      } else {
	suml *= factors[i_left[i] - 1];
      }
      /* Remove from right */
      i_right[i_left[i]] = 0;
    }

#ifdef PRINT_FACTORS
    printf("x ");
#endif

    /* The rest -> right */
    for (i = 1; i <= n; i++) {
      if (i_right[i] != 0) {
#ifdef PRINT_FACTORS
	printf("%ld ", factors[i - 1]);
#endif
	if (sumr == 0) {
	  sumr = factors[i - 1];
	} else {
	  sumr *= factors[i - 1];
	}
      }
    }
#ifdef PRINT_FACTORS
    printf(" (%d x %d)\n", suml, sumr);
#else
    printf("%dx%d\n", suml, sumr);
#endif

    return;
  }

  /* for this k'th element of the v, try all start..n
   * elements in that position
   */
  for (i = start; i <= n; i++) {
    i_left[k] = i;

    /* recurse combinations from i+1..n */
    combinations(i+1, n, k+1);
  }
}

static void print_combinations(void)
{
   int k; /* Number of factors on left side */

   for (k = 1; k < n_fac; k++) {
      maxk = k;
      combinations(1, n_fac, 1);
   }
}


int main(int argc, char *argv[])
{
   mpz_t N;

   if (argc != 2) {
      printf("\nUsage: %s <NUM_PIXELS>\n\n", argv[0]);

      printf("Program to print out all the ways NUM_PIXELS can be arranged\n"
             "in a 2d plane. May contain duplicates.\n\n");

      printf("EXAMPLES\n\n");

      printf("Show all the ways a 360 x 288 pixles image can be rearranged:\n\n"
             "%s $((360*288)) | sort -n | uniq\n\n", argv[0]);

      printf("Convert a 872 x 140 pixels image to all possible sizes, not\n"
             "by stretching, but by rearranging the pixels (using convert\n"
             "from the imagemagick package):\n\n"
             "convert image.png image.rgb\n"
             "for sz in `%s $((872*140)) | sort -n | uniq`; do\n", argv[0]);
      printf("  convert -depth 8 -size \"$sz\" image.rgb img$sz.png\n"
             "done\n");

      return 1;
   }

   mpz_init(N);
   load_gmp_string(N, argv[1]);

   if (!get_factors(N)) {
      print_combinations();
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
