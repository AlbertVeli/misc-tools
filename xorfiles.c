/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "hextools.h"
#include "xor.h"
#include "map.h"

#define PROGRAM_NAME "xorfiles"
#define PROGRAM_VERSION "0.1"
#define PROGRAM_NAME_VERSION PROGRAM_NAME "-" PROGRAM_VERSION

struct opts
{
   /* Mandatory */
   char *file1;
   char *file2;

   /* Optional */
   int xnor;
} opt;

/* Program documentation. */
static char *prog_doc =
   PROGRAM_NAME_VERSION
   "\nXor files together.\n\n"
   "USAGE\n\n" PROGRAM_NAME " [OPTIONS] <file1> <file2>\n\n"
   "MANDATORY ARGUMENTS\n\n"
   "file1       - first file\n"
   "file2       - second file\n\n"
   "If lengths differs file1 decides length of the output.\n"
   "To xor crypt, use file1 as text and file2 as repeating key.\n\n"

   "OPTIONS\n\n"
   "-n          - use xnor instead of standard xor\n"
   "-h          - print this help text\n\n";

void print_usage(void)
{
   printf("%s", prog_doc);
}

int parse_args(int argc, char **argv)
{
   int c;

   /* Default values. */
   opt.xnor = 0;

   /* Parse optional arguments */
   opterr = 0;
   while ((c = getopt (argc, argv, "n")) != -1) {

      switch (c) {

      case 'n':
         opt.xnor = 1;
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

   if (argc != optind + 2) {
      puts("Error: wrong number of mandatory arguments");
      return 0;
   }

   /* Mandatory arguments */
   opt.file1 = argv[optind++];
   opt.file2 = argv[optind++];

   return 1;
}

int main(int argc, char *argv[])
{
   char *b1;
   char *b2;
   int b1len;
   int b2len;
   char *xorbuf;

   if (!parse_args(argc, argv)) {
      print_usage();
      return 1;
   }

   if (!init_map(opt.file1)) {
      perror(opt.file1);
      return 1;
   }

   if (!init_map2(opt.file2)) {
      perror(opt.file2);
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
      if (opt.xnor) {
         rep_xnor(xorbuf, b1, b2, b1len, b2len);
      } else {
         rep_xor(xorbuf, b1, b2, b1len, b2len);
      }
   } else {
      /* One Time Pad */
      if (opt.xnor) {
         otp_xnor(xorbuf, b1, b2, b1len);
      } else {
         otp_xor(xorbuf, b1, b2, b1len);
      }
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
