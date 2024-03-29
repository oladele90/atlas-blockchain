#include "transaction.h"

/**
 * coinbase_create - Create a coinbase transaction
 * @receiver: Pointer to the EC_KEY of the receiver
 * @block_index: Index of the block
 *
 * Return: Pointer to the newly created transaction
 */

transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index)
{
	tx_in_t *new_in;
	tx_out_t *new_out;
	transaction_t *transaction;
	uint8_t pub[EC_PUB_LEN];

	new_in = calloc(sizeof(tx_in_t), 1);
	memcpy(new_in->tx_out_hash, &block_index, 4);
	ec_to_pub(receiver, pub);
	new_out = tx_out_create(COINBASE_AMOUNT, pub);
	sha256((int8_t *)new_out,
		sizeof(new_out->amount) + sizeof(new_out->pub), new_out->hash);
	transaction = calloc(sizeof(transaction_t), 1);
	transaction->outputs = llist_create(MT_SUPPORT_FALSE);
	transaction->inputs = llist_create(MT_SUPPORT_FALSE);
	llist_add_node(transaction->inputs, new_in, ADD_NODE_REAR);
	llist_add_node(transaction->outputs, new_out, ADD_NODE_REAR);
	transaction_hash(transaction, transaction->id);
	return (transaction);
}
