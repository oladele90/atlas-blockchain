#include "transaction.h"

static int check_inputs(int tx_in_amt, int unspent_amt, transaction_t const *transaction, llist_t *all_unspent)
{
    int i, j, match_flag;
    tx_in_t* tx_in_index;
    unspent_tx_out_t *unspent_index;

    for (i = 0; i < tx_in_amt; i++)
    {
        match_flag = 0;
        tx_in_index = llist_get_node_at(transaction->inputs, i);
        for (j = 0; j < unspent_amt; j++)
        {
            unspent_index = llist_get_node_at(all_unspent, j);
            if (memcmp(&tx_in_index->block_hash, unspent_index->block_hash, SHA256_DIGEST_LENGTH) == 0 &&
                memcmp(&tx_in_index->tx_id, unspent_index->tx_id, SHA256_DIGEST_LENGTH) == 0 && 
                ec_verify(ec_from_pub((uint8_t const *)unspent_index->out.pub), transaction->id, SHA256_DIGEST_LENGTH, &tx_in_index->sig) == 1)
		        {
                    match_flag = 1;
                    break;
                }
        }
        if (match_flag != 1)
            return (0);
    }
    return (1);
}
int transaction_is_valid(transaction_t const *transaction, llist_t *all_unspent)
{
    int tx_in_amt, tx_out_amt, unspent_amt;
    uint8_t hash_buf[SHA256_DIGEST_LENGTH];

    if (memcmp(transaction_hash(transaction, hash_buf), &transaction->id, SHA256_DIGEST_LENGTH) != 0)
        return (0);

    tx_in_amt = llist_size(transaction->inputs);
    tx_out_amt = llist_size(transaction->outputs);
    unspent_amt = llist_size(all_unspent);
    return (check_inputs(tx_in_amt, unspent_amt, transaction, all_unspent));
}