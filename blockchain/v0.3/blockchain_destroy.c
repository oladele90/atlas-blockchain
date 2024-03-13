#include "blockchain.h"

/**
 * blockchain_destroy - Frees a blockchain and its associated blocks
 * @blockchain: Pointer to the blockchain to be destroyed
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	llist_destroy((llist_t *)blockchain->chain, 1, (node_dtor_t)block_destroy);
	llist_destroy(blockchain->unspent, 1, free);
	free(blockchain);
}
