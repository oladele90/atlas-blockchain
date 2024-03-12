#include "blockchain.h"

/**
 * blockchain_create - Creates a new blockchain with a genesis block
 *
 * Return: A pointer to the newly created blockchain
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *new_chain = calloc(1, sizeof(blockchain_t));
	block_t *new_block = calloc(1, sizeof(block_t));

	if (!new_block || !new_chain)
	{
		free(new_chain);
		return (NULL);
	}
	new_chain->chain = llist_create(MT_SUPPORT_FALSE);
	if (!new_chain->chain)
	{
		free(new_block);
		free(new_chain);
		return (NULL);
	}

	memcpy(new_block->data.buffer, "Holberton School",
			strlen("Holberton School") + 1);
	new_block->data.len = strlen((const char *)new_block->data.buffer);
	new_block->info.timestamp = 1537578000;
	memcpy(new_block->hash, "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d"
							"\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09"
							"\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51"
							"\x58\x03", SHA256_DIGEST_LENGTH);

	llist_add_node(new_chain->chain, new_block, ADD_NODE_FRONT);
	new_chain->unspent = llist_create(MT_SUPPORT_FALSE);
	return (new_chain);
}
