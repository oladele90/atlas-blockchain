#include "blockchain.h"
/**
 * block_mine - mines a block
 * @block: block to mine
*/
void block_mine(block_t *block)
{
	uint8_t buf[SHA256_DIGEST_LENGTH];

	for (; 1 == 1; block->info.nonce++)
	{
		block_hash(block, buf);
		if (hash_matches_difficulty(buf, block->info.difficulty))
		{
			memcpy(block->hash, buf, SHA256_DIGEST_LENGTH);
			break;
		}
	}
}
