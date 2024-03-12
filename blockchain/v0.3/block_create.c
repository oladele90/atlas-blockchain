#include "blockchain.h"

block_t *block_create(block_t const *prev, int8_t const *data,
												uint32_t data_len)
{
	time_t current;
	block_t *new_block = calloc(1, sizeof(block_t));

	current = time(NULL);
	memcpy(new_block->data.buffer, data, data_len);
	new_block->data.len = data_len;
	new_block->info.index = prev->info.index + 1;
	new_block->info.timestamp = current;
	memcpy(new_block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	new_block->transactions = llist_create(MT_SUPPORT_FALSE);

	return (new_block);
}
