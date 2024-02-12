#include "blockchain.h"

/**
 * block_is_valid - Checks if a block is valid
 * @block: Pointer to the block to be validated
 * @prev_block: Pointer to the previous block in the blockchain
 *
 * Return: 0 if the block is valid, 1 otherwise
 */

int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH] = {0};
	blockchain_t *genesis;
	block_t *first;
	int check;

	if (!block || (!prev_block && block->info.index != 0))
		return (1);
	if (block->info.index == 0)
	{
		genesis = blockchain_create();
		first = llist_get_head(genesis->chain);
		check = memcmp(first, block, sizeof(block_t));
		blockchain_destroy(genesis);
		if (check != 0)
			return (1);
		return (0);
	}
	
	if (block->info.index != prev_block->info.index + 1)
		return (1);
	if (!block_hash(prev_block, hash_buf) ||
		memcmp(hash_buf, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (!block_hash(block, hash_buf) ||
		memcmp(hash_buf, block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);
	return (0);
}
