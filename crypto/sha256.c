#include "hblk_crypto.h"

uint8_t *sha256(int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH])
{
    SHA256_CTX hash;
    
    if (digest == NULL)
        return NULL;

    SHA256_Init(&hash);
    SHA256_Update(&hash, s, len);
    SHA256_Final(digest, &hash);

    return digest;
}
