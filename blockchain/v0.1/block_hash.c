#include "blockchain.h"


uint8_t *block_hash(block_t const *block, uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
    SHA256_CTX c;

    SHA256_Init(&c);
    SHA256_Update(&c, (void *)&(block->info), SHA256_DIGEST_LENGTH);

    SHA256_Final(hash_buf, &c);
    return (hash_buf);
}