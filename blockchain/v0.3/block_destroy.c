#include "blockchain.h"

/**
 * block_destroy - Frees a block and its allocated memory
 * @block: Pointer to the block to be destroyed
 */

void block_destroy(block_t *block)
{
	free(block);
}
