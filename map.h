#ifndef __MAP_H
#define __MAP_H

/* ~~=) All Rights Reversed (=~~ */

extern char *map;
extern char *map2;
extern void free_map(void);
extern int init_map(const char *filename);
extern int get_map_len(void);
extern int init_map2(const char *filename);
extern int get_map2_len(void);


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */

#endif
