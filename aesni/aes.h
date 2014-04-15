#ifndef __AES_H
#define __AES_H

/* ~~=) All Rights Reversed (=~~ */

/* Low level stuff in aes128.h */
#include "aes128.h"

/* Modes etc */
extern void aes_set_keys(const char *key);
extern void aes_ecb_encrypt(const char *msg, char *ct, int len);
extern void aes_ecb_decrypt(const char *ct, char *msg, int len);
extern void aes_cbc_encrypt(char *msg, char *ct, char *iv, int len);
extern void aes_cbc_decrypt(const char *ct, char *msg, char *iv, int len);
extern void aes_ctr_encrypt(const char *msg, char *ct, char *iv, int len);
extern void aes_ctr_decrypt(const char *ct, char *msg, char *iv, int len);


/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */

#endif /* __AES_H */
