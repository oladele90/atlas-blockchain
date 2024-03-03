#include "transaction.h"

/**
 * mem_append - Appends data to a buffer
 * @buf: Pointer to the buffer to append data to
 * @data: Pointer to the data to append
 * @pointer: Pointer to the current position in the buffer
 *
 * This function appends the specified data to the buffer at the current
 * position indicated by the pointer. The pointer is updated to point to the
 * next available position in the buffer after appending the data.
 */
static void mem_append(uint8_t *buf, uint8_t *data, size_t *pointer)
{
	memcpy(buf + *pointer, data, 32);
	*pointer += 32;
}

/**
 * transaction_hash - Computes the hash of a transaction
 * @transaction: Pointer to the transaction to hash
 * @hash_buf: Buffer to store the resulting hash
 *
 * Return: Pointer to the resulting hash
 */

uint8_t *transaction_hash(
	transaction_t const *transaction,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	int in_size, out_size, i;
	uint8_t *buf;
	size_t pointer = 0;
	tx_in_t *node_in;
	tx_out_t *node_out;

	in_size = llist_size(transaction->inputs);
	out_size = llist_size(transaction->outputs);
	buf = malloc((in_size * 96) + (out_size * 32));

	for (i = 0; i < in_size; i++)
	{
		node_in = llist_get_node_at(transaction->inputs, i);
		mem_append(buf, node_in->block_hash, &pointer);
		mem_append(buf, node_in->tx_id, &pointer);
		mem_append(buf, node_in->tx_out_hash, &pointer);
	}

	for (i = 0; i < out_size; i++)
	{
		node_out = llist_get_node_at(transaction->outputs, i);
		mem_append(buf, node_out->hash, &pointer);
	}

	sha256((const int8_t *)buf, (in_size * 96) + (out_size * 32), hash_buf);
	free(buf);
	return (hash_buf);
}
