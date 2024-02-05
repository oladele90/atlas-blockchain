#include "blockchain.h"


uint8_t *block_hash(block_t const *block,
					uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{

    sha256((int8_t const *)&(block->info),
			(sizeof(block->info) + block->data.len), hash_buf);
    return (hash_buf);
}