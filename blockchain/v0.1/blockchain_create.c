#include "blockchain.h"

/**
 * blockchain_create - Creates a new blockchain with a genesis block
 *
 * Return: A pointer to the newly created blockchain
 */

blockchain_t *blockchain_create(void)
{
	blockchain_t *new_chain = malloc(sizeof(blockchain_t));
	block_t *new_block = malloc(sizeof(block_t));
	block_info_t *new_info = malloc(sizeof(block_info_t));
	block_data_t *new_data = malloc(sizeof(block_data_t));

	memcpy(new_data->buffer, "Holberton School", strlen("Holberton School") + 1);
	new_data->len = strlen((const char *)new_data->buffer);
	new_info->index = 0;
	new_info->difficulty = 0;
	new_info->timestamp = 1537578000;
	new_info->nonce = 0;
	memset(new_info->prev_hash, 0, SHA256_DIGEST_LENGTH);
	memcpy(new_block->hash, "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d"
							"\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09"
							"\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51"
							"\x58\x03", SHA256_DIGEST_LENGTH);
	memcpy(&new_block->info, new_info, sizeof(block_info_t));
	memcpy(&new_block->data, new_data, sizeof(block_data_t));
	new_chain->chain = llist_create(MT_SUPPORT_FALSE);
	llist_add_node(new_chain->chain, new_block, ADD_NODE_REAR);

	return (new_chain);


}
