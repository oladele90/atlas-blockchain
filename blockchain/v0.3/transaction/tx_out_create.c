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
    SHA256_CTX c;

    if (!amount || !pub)
        return (NULL);
    new_tx = calloc(sizeof(tx_out_t), 1);
    memset(new_tx->pub, 0, EC_PUB_LEN);
    memset(new_tx->hash, 0, SHA256_DIGEST_LENGTH + 1);
    new_tx->amount = amount;
    memcpy(&new_tx->pub, pub, EC_PUB_LEN);

	SHA256_Init(&c);
	SHA256_Update(&c, (uint8_t const *)pub, EC_PUB_LEN);
	SHA256_Update(&c, (uint8_t const *)&amount, sizeof(uint32_t));

	SHA256_Final(new_tx->hash, &c);
    
    return (new_tx);
}
