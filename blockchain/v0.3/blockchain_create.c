#include "blockchain.h"


/**
 * blockchain_create - initializes the genesis block of a blockchain
 * Return: pointer to the blockchain
*/
blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain = calloc(1, sizeof(blockchain_t));
	block_t *genesis_block = calloc(1, sizeof(block_t));
	uint8_t data[] = {'H', 'o', 'l', 'b', 'e', 'r', 't', 'o', 'n', ' ',
										 'S', 'c', 'h', 'o', 'o', 'l', '\0'};

	genesis_block->info.timestamp = 1537578000;

	memset(genesis_block->info.prev_hash, 0, BLOCKCHAIN_DATA_MAX);

	genesis_block->data.len = strlen((char *)(data));
	memcpy(genesis_block->data.buffer, data, genesis_block->data.len);

	memcpy(genesis_block->hash, GENESIS_BLOCK_HASH, SHA256_DIGEST_LENGTH);

	blockchain->chain = llist_create(MT_SUPPORT_TRUE);
	llist_add_node(blockchain->chain, genesis_block, ADD_NODE_FRONT);
	blockchain->unspent = llist_create(MT_SUPPORT_FALSE);
	return (blockchain);
}