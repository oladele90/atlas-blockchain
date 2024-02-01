#include "blockchain.h"

block_t *block_create(block_t const *prev, int8_t const *data,
					   uint32_t data_len)
{
	block_t *new_block = calloc(1, sizeof(block_t));
	uint32_t d_len = data_len > BLOCKCHAIN_DATA_MAX ?
data_len : BLOCKCHAIN_DATA_MAX;

	if (!new_block)
	{
		free(new_block);
		return (NULL);
	}

	memcpy(new_block->data.buffer, data, data_len);

	new_block->data.len = d_len;
	new_block->info.timestamp = syscall(SYS_time, NULL);
	new_block->info.index = prev->info.index + 1;
	return (new_block);
}
