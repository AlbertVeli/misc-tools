/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"

int nbits = 0;

int shiftbyteleft(char *byte, int carry)
{
  int retcarry = (*byte) >> (8 - nbits);
  *byte = (*byte) << nbits;
  *byte = (*byte) | carry;

  return retcarry;
}

int main(int argc, char *argv[])
{
  char *b1;
  int b1len;
  int i;
  int carry;
  char *p1, *p2;
  char *buf;

  if (argc != 3) {
    printf("bitshift whole file n bits left, throw away overflow bits\n");
    printf("Usage: %s <file> <n>\n", argv[0]);
    return 1;
  }

  nbits = strtoul(argv[2], NULL, 0);
  if (nbits < 1 || nbits > 7) {
    printf("nbits should be between 1 and 7\nuse dd to cut off whole bytes\n");
    return 1;
  }

  if (!init_map(argv[1])) {
    perror(argv[1]);
    return 1;
  }

  b1 = map;
  b1len = get_map_len();

  buf = (char *)malloc(b1len);
  if (!buf) {
    perror("out of memory");
    free_map();
    return 1;
  }
  
  p1 = &b1[b1len - 1];
  p2 = &buf[b1len - 1];
  carry = 0;
  
  for (i = 0; i < b1len; i++) {
    *p2 = *p1;
    carry = shiftbyteleft(p2, carry);
    p1--;
    p2--;
  }

  free_map();

  p2 = buf;
  for (i = 0; i < b1len; i++) {
    printf("%c", *p2++);
  }

  free(buf);

  return 0;
}
