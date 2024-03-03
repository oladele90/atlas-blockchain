#include "transaction.h"

unspent_tx_out_t *unspent_tx_out_create(uint8_t block_hash[SHA256_DIGEST_LENGTH],
                                        uint8_t tx_id[SHA256_DIGEST_LENGTH],
                                        tx_out_t const *out)
{
    unspent_tx_out_t new_u_tx;

    if (!tx_id || !block_hash || !out)
        return (NULL);
    new_u_tx = calloc(1, sizeof(unspent_tx_out_t));
    memcpy(&new_u_tx->block_hash, block_hash, SHA256_DIGEST_LENGTH);
    memcpy(&new_u_tx->tx_id, tx_id, SHA256_DIGEST_LENGTH);
    memcpy(&new_u_tx->out, out, sizeof(tx_out_t));
    return (new_u_tx);
}