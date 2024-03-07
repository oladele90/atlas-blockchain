#include "transaction.h"

int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
    uint8_t hash_buf[SHA256_DIGEST_LENGTH];
    tx_in_t *input;
    tx_out_t *output;


    if (memcmp(transaction_hash(coinbase, hash_buf), coinbase->id, SHA256_DIGEST_LENGTH))
        return (0);

    if (llist_size(coinbase->inputs) != 1 || llist_size(coinbase->outputs) != 1)
        return (0);
    
    input = llist_get_node_at(coinbase->inputs , 0);
    output = llist_get_node_at(coinbase->outputs, 0);

    if (memcmp(input->tx_out_hash, &block_index, 4))
        return (0);
    
    if (*input->block_hash || *input->tx_id)
        return (0);
    
    if (output->amount != COINBASE_AMOUNT)
        return (0);
    
    return (1);
}