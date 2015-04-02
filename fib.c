/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <unistd.h>
#include <gmp.h>

#include "gmptools.h"

#define PROGRAM_NAME "fib"
#define PROGRAM_VERSION "0.1"
#define PROGRAM_NAME_VERSION PROGRAM_NAME "-" PROGRAM_VERSION

struct opts
{
   /* Mandatory */
   char *number;

   /* Optional */
   int sum;
} opt;

/* Program documentation. */
static char *prog_doc =
   PROGRAM_NAME_VERSION
   "\nCalculate nth fibonacci number.\n\n"
   "USAGE\n\n" PROGRAM_NAME " [OPTIONS] <number>\n\n"
   "MANDATORY ARGUMENTS\n\n"
   "number      - decimal or hex string\n\n"
   "OPTIONS\n\n"
   "-s          - sum of first n fib.numbers\n"
   "-h          - print this help text\n\n";

void print_usage(void)
{
   printf("%s", prog_doc);
}

int parse_args(int argc, char **argv)
{
   int c;

   /* Default values. */
   opt.sum = 0;

   /* Parse optional arguments */
   opterr = 0;
   while ((c = getopt (argc, argv, "sh")) != -1) {

      switch (c) {

      case 's':
         opt.sum = 1;
         break;

      case 'h':
         /* Just print help text */
         return 0;

      case '?':
         fprintf(stderr, "Error: unknown option -%c\n\n", optopt);
         return 0;

      default:
         return 0;
      }
   }

   if (argc != optind + 1) {
      puts("Error: wrong number of mandatory arguments");
      return 0;
   }

   /* Mandatory arguments */
   opt.number = argv[optind];

   return 1;
}

/* Calculate num:th fibonacci number */
void fib(mpz_t sum, mpz_t num)
{
   mpz_t first, second, count;

   if (mpz_cmp_ui(num, 2) < 0) {
      mpz_set(sum, num);
      return;
   }

   mpz_init(first);
   mpz_init_set_ui(second, 1);
   mpz_init_set_ui(count, 1);


   while(mpz_cmp(num, count)) {
      mpz_add(sum, first, second);
      mpz_set(first, second);
      mpz_set(second, sum);
      mpz_add_ui(count, count, 1);
   }

   mpz_clear(count);
   mpz_clear(second);
   mpz_clear(first);
}


int main(int argc, char *argv[])
{
   mpz_t n, sum;

   if (!parse_args(argc, argv)) {
      print_usage();
      return 1;
   }

   mpz_init(n);
   load_gmp_string(n, opt.number);

   /* Sum of first n fibonacci numbers is fib(n + 2) - 1.
    *
    * For instance, sum of first 5 fib numbers is:
    *
    * fib(5+2) - 1 = 13 - 1 = 12
    * or 1 + 1 + 2 + 3 + 5 = 12
    *
    *      n : 0  1  2  3  4  5  6  7   8
    * fib(n) : 0  1  1  2  3  5  8  13  21
    */
   if (opt.sum) {
      /* n + 2 */
      mpz_add_ui(n, n, 2);
   }

   mpz_init(sum);
   fib(sum, n);

   if (opt.sum) {
      /* - 1 */
      mpz_sub_ui(sum, sum, 1);
   }

   gmp_printf("%Zd\n", sum);

   mpz_clear(n);
   mpz_clear(sum);

   return 0;
}


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */
