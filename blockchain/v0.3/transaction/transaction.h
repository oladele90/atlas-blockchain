#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_
#include "blockchain.h"

unspent_tx_out_t *unspent_tx_out_create(uint8_t block_hash[SHA256_DIGEST_LENGTH],
                                        uint8_t tx_id[SHA256_DIGEST_LENGTH],
                                        tx_out_t const *out);
#endif