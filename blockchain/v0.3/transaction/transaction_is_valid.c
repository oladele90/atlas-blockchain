#include "transaction.h"

static int check_inputs(int tx_in_size, int unspent_size, int tx_out_size,
	transaction_t const *transaction, llist_t *all_unspent)
{
	int i, j, match_flag, in_sum = 0, out_sum = 0;
	tx_in_t* tx_in_index;
	unspent_tx_out_t *unspent_index;
	tx_out_t  *tx_out_index;

	for (i = 0; i < tx_in_size; i++)
	{
		match_flag = 0;
		tx_in_index = llist_get_node_at(transaction->inputs, i);
		for (j = 0; j < unspent_size; j++)
		{
			unspent_index = llist_get_node_at(all_unspent, j);
			if (memcmp(&tx_in_index->tx_out_hash,
				unspent_index->out.hash, SHA256_DIGEST_LENGTH) == 0 &&
				memcmp(&tx_in_index->tx_id, unspent_index->tx_id,
				SHA256_DIGEST_LENGTH) == 0 && 
				memcmp(&tx_in_index->block_hash,
				unspent_index->block_hash, SHA256_DIGEST_LENGTH) == 0 &&
				ec_verify(ec_from_pub((uint8_t const *)unspent_index->out.pub),
				transaction->id, SHA256_DIGEST_LENGTH, &tx_in_index->sig) == 1)
				{
					in_sum += unspent_index->out.amount;
					match_flag = 1;
					break;
				}
		}
		if (match_flag != 1)
			return (0);
	}
	for (i = 0; i < tx_out_size; i++)
	{
		tx_out_index = llist_get_node_at(transaction->outputs, i);
		out_sum += tx_out_index->amount;
	}
	if (out_sum != in_sum)
		return (0);

	return (1);
}
int transaction_is_valid(transaction_t const *transaction,
	llist_t *all_unspent)
{
	int tx_in_size, unspent_size, tx_out_size;
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];

	if (memcmp(transaction_hash(transaction, hash_buf),
		&transaction->id, SHA256_DIGEST_LENGTH) != 0)
		return (0);

	tx_in_size = llist_size(transaction->inputs);
	tx_out_size = llist_size(transaction->outputs);
	unspent_size = llist_size(all_unspent);
	return (check_inputs(tx_in_size, unspent_size, tx_out_size,
		transaction, all_unspent));
}
