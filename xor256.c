/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "hextools.h"
#include "xor.h"
#include "map.h"

#define PROGRAM_NAME "xor256"
#define PROGRAM_VERSION "0.1"
#define PROGRAM_NAME_VERSION PROGRAM_NAME "-" PROGRAM_VERSION

struct opts
{
   /* Mandatory */
   char *filename;

   /* Optional */
   int xnor;

   /* Optional */
   char *outsuffix;
} opt;

/* Program documentation. */
static char *prog_doc =
   PROGRAM_NAME_VERSION
   "\nXor file with all 256 combinations of 1 byte.\n\n"
   "USAGE\n\n" PROGRAM_NAME " [OPTIONS] <filename>\n\n"
   "MANDATORY ARGUMENTS\n\n"
   "filename    - name of file to xor\n\n"
   "OPTIONS\n\n"
   "-n          - use xnor instead of normal xor\n"
   "-f <suffix> - write output into 256 separate files\n"
   "              named 0-255.suffix (instead of stdout).\n"
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
   opt.outsuffix = NULL;

   /* Parse optional arguments */
   opterr = 0;
   while ((c = getopt (argc, argv, "nf:h")) != -1) {

      switch (c) {

      case 'n':
         opt.xnor = 1;
         break;

      case 'f':
         opt.outsuffix = optarg;
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
   opt.filename = argv[optind];

   return 1;
}


int main(int argc, char *argv[])
{
   char *b1;
   int b1len;
   char *xorbuf = NULL;
   int i, b;
   char *p;
   FILE *fp;
   char path[32];

   if (!parse_args(argc, argv)) {
      print_usage();
      return 1;
   }

   if (!init_map(opt.filename)) {
      perror(opt.filename);
      return 1;
   }

   b1 = map;
   b1len = get_map_len();

   xorbuf = malloc(b1len);
   if (!xorbuf) {
      fprintf(stderr, "Could not alloc %d bytes for xorbuf\n", b1len);
      free_map();
      return 1;
   }

   if (opt.xnor) {
      for (b = 0; b < 256; b++) {
         memcpy(xorbuf, b1, b1len);
         p = xorbuf;
         for (i = 0; i < b1len; i++) {
            *p = ~(*p ^ b);
            p++;
         }
         if (opt.outsuffix) {
            sprintf(path, "%03d.%s", b, opt.outsuffix);
            fp = fopen(path, "w");
            if (!fp) {
               perror(path);
            } else {
               fwrite(xorbuf, 1, b1len, fp);
               fclose(fp);
            }
         } else {
            out_raw(xorbuf, b1len);
         }
      }
   } else {
      for (b = 0; b < 256; b++) {
         memcpy(xorbuf, b1, b1len);
         p = xorbuf;
         for (i = 0; i < b1len; i++) {
            *p = *p ^ b;
            p++;
         }
         if (opt.outsuffix) {
            sprintf(path, "%03d.%s", b, opt.outsuffix);
            fp = fopen(path, "w");
            if (!fp) {
               perror(path);
            } else {
               fwrite(xorbuf, 1, b1len, fp);
               fclose(fp);
            }
         } else {
            out_raw(xorbuf, b1len);
         }
      }
   }

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
