/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const char *progname = NULL;

void usage_and_quit(char *msg)
{
   fprintf(stderr, "\nError: %s\n\n", msg ? msg : "");
   fprintf(stderr,
           "Usage: %s <ip/len>\n"
           "Example: %s 192.168.1.1/24\n", progname, progname);
   exit(1);
}

void print_ip(uint32_t ip)
{
   printf("%d.%d.%d.%d",
          (ip >> 24) & 0xff,
          (ip >> 16) & 0xff,
          (ip >>  8) & 0xff,
          (ip >>  0) & 0xff);
}

int main(int argc, char *argv[])
{
   uint32_t ip;
   uint32_t mask;
   int len;
   int tmp;
   char *s, *p;

   progname = argv[0];

   if (argc != 2) {
      usage_and_quit("Wrong number of arguments");
   }

   ip = 0;
   p = argv[1];

   /* First quad */
   s = p;
   while(*p >= '0' && *p <= '9') p++;
   if (*p != '.') {
      usage_and_quit("Expected a \".\"");
   }
   tmp = strtoul(s, NULL, 10);
   ip += tmp << 24;
   p++;

   /* Second quad (hey, could put this in a loop) */
   s = p;
   while(*p >= '0' && *p <= '9') p++;
   if (*p != '.') {
      usage_and_quit("Expected a \".\"");
   }
   tmp = strtoul(s, NULL, 10);
   ip += tmp << 16;
   p++;

   /* Third quad */
   s = p;
   while(*p >= '0' && *p <= '9') p++;
   if (*p != '.') {
      usage_and_quit("Expected a \".\"");
   }
   tmp = strtoul(s, NULL, 10);
   ip += tmp << 8;
   p++;

   /* Fourth quad */
   s = p;
   while(*p >= '0' && *p <= '9') p++;
   if (*p != '/') {
      usage_and_quit("Expected a \"/\"");
   }
   tmp = strtoul(s, NULL, 10);
   ip += tmp;
   p++;

   /* Subnet length */
   s = p;
   len = strtoul(s, NULL, 10);

   /* Subnet mask */
   mask = 0;
   for (tmp = 0; tmp < len; tmp++) {
      mask |= 1 << (31 - tmp);
   }

   /* Zero out ip-bits according to mask to get network address */
   ip &= mask;
   printf("Network:   ");
   print_ip(ip);
   printf("\n");

   /* Set ip-bits according to inverted mask to get broadcast address */
   ip |= (~mask);
   printf("Broadcast: ");
   print_ip(ip);
   printf("\n");

   /* Note, use addresses in the range between those two */

   return 0;
}


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */
