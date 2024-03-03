#include "transaction.h"

/**
 * tx_in_create - Creates a new transaction input
 * @unspent: The unspent transaction output to create input from
 *
 * Return: If the transaction input is successfully created, a pointer to the
 *         newly created transaction input. Otherwise, NULL.
 */

tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *new_tx_in;

	if (!unspent)
		return (NULL);
	new_tx_in = calloc(sizeof(tx_in_t), 1);

	memcpy(&new_tx_in->block_hash, unspent->block_hash, SHA256_DIGEST_LENGTH);
	memcpy(&new_tx_in->tx_id, unspent->tx_id, SHA256_DIGEST_LENGTH);
	memcpy(&new_tx_in->tx_out_hash, unspent->out.hash, SHA256_DIGEST_LENGTH);
	return (new_tx_in);
}
