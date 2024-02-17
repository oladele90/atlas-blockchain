#include "blockchain.h"

/**
 * blockchain_destroy - Frees a blockchain and its associated blocks
 * @blockchain: Pointer to the blockchain to be destroyed
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	llist_destroy(blockchain->chain, llist_size(blockchain->chain), NULL);
	blockchain->chain = NULL;
	free(blockchain);
}
