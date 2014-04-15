#ifndef __AES128_H
#define __AES128_H

/* ~~=) All Rights Reversed (=~~ */

#include <stdint.h>

#define AES128_MAXNR 10
#define AES_BLOCK_SIZE 16

struct aes128_key_st {
   uint32_t rd_key[4 * (AES128_MAXNR + 1)];
};
typedef struct aes128_key_st AES128_KEY;

int aesni_128_set_encrypt_key(const char *userKey, AES128_KEY *key);
int aesni_128_set_decrypt_key(const char *userKey, AES128_KEY *key);
void aesni_128_encrypt(const char *msg, char *ct, const AES128_KEY *key);
void aesni_128_decrypt(const char *ct, char *msg, const AES128_KEY *key);

/**
 * Local Variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 3
 * End:
 */

#endif /* __AES128_H */
