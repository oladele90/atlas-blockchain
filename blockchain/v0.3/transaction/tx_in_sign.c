#include "transaction.h"

/**
 * tx_in_sign - signs a transaction input
 * @in: transaction input structure
 * @tx_id: contains the id of the transaction
 * @sender: contains the private key of the reciever of coins
 * @all_unspent: list of all unspent transaction outputs
 * Return: the sig struct
*/
sig_t *tx_in_sign(tx_in_t *in,
	uint8_t const tx_id[SHA256_DIGEST_LENGTH],
		EC_KEY const *sender, llist_t *all_unspent)
{
	uint8_t pub_buf[EC_PUB_LEN];
	unspent_tx_out_t *node;
	sig_t *sig;
	int i, list_size;


	list_size = llist_size(all_unspent);
	ec_to_pub(sender, pub_buf);
	for (i = 0; i < list_size; i++)
	{
		node = llist_get_node_at(all_unspent, i);
		if (memcmp(node->out.pub, pub_buf, EC_PUB_LEN) == 0)
		{
			ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &in->sig);
			sig = &in->sig;
			return (sig);
		}
	}
	return (NULL);
}
