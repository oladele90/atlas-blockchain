#include "blockchain.h"

/**
 * block_hash - Computes the hash of a block using SHA-256 algorithm
 * @block: Pointer to the block to be hashed
 * @hash_buf: Buffer to store the resulting hash
 *
 * Return: Pointer to the computed hash buffer
 */

uint8_t *block_hash(block_t const *block,
					uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	SHA256_CTX c;

	SHA256_Init(&c);
	SHA256_Update(&c, (uint8_t const *)&(block->info), sizeof(block->info));
	SHA256_Update(&c, (uint8_t const *)&(block->data), (block->data.len));

	SHA256_Final(hash_buf, &c);
	return (hash_buf);
}
