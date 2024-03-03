#include "blockchain.h"

/**
 * tx_out_create - creates a new transaction output structure
 * @amount: the amount of the transaction
 * @pub: the public key to include in the transaction output
 *
 * Return: pointer to the newly created transaction output structure,
 * or NULL if memory allocation fails or if @amount is 0 or if @pub is NULL
 */

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *new_tx;

	if (!amount || !pub)
		return (NULL);
	new_tx = calloc(sizeof(tx_out_t), 1);
	new_tx->amount = amount;
	memcpy(&new_tx->pub, pub, EC_PUB_LEN);
	sha256((int8_t *)new_tx, sizeof(new_tx->amount) + sizeof(new_tx->pub), new_tx->hash);


	return (new_tx);
}
