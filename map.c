/* ~~=) All Rights Reversed (=~~ */

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Memory mapping */
char *map = NULL;
static struct stat mapstat;

char *map2 = NULL;
static struct stat mapstat2;

void free_map(void)
{
   if (map) {
      munmap(map, mapstat.st_size);
      map = NULL;
   }
   if (map2) {
      munmap(map2, mapstat2.st_size);
      map2 = NULL;
   }
}

int init_map(const char *filename)
{
   int ret = 0;
   int fd = open(filename, O_RDONLY);

   if (fd < 0) {
      perror(filename);
      goto out;
   }

   if (fstat(fd, &mapstat) < 0) {
      perror(filename);
      goto out2;
   }

   map = mmap(NULL, mapstat.st_size, PROT_READ, MAP_SHARED, fd, 0);
   if (map == MAP_FAILED) {
      perror(filename);
      goto out2;
   }

   ret = 1;

 out2:

   close(fd);

 out:

   return ret;
}

int init_map2(const char *filename)
{
   int ret = 0;
   int fd = open(filename, O_RDONLY);

   if (fd < 0) {
      perror(filename);
      goto out;
   }

   if (fstat(fd, &mapstat2) < 0) {
      perror(filename);
      goto out2;
   }

   map2 = mmap(NULL, mapstat2.st_size, PROT_READ, MAP_SHARED, fd, 0);
   if (map == MAP_FAILED) {
      perror(filename);
      goto out2;
   }

   ret = 1;

 out2:

   close(fd);

 out:

   return ret;
}

int get_map_len(void)
{
   return mapstat.st_size;
}

int get_map2_len(void)
{
   return mapstat2.st_size;
}


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */
