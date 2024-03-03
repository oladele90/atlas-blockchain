#include "transaction.h"

static void mem_append(uint8_t *buf, uint8_t *data, size_t *pointer)
{
    memcpy(buf + *pointer, data, 32);
    *pointer += 32;
}

uint8_t *transaction_hash(
    transaction_t const *transaction,
    uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
    int in_size, out_size, i;
    uint8_t *buf;
    size_t pointer = 0;
    tx_in_t *node_in;
    tx_out_t *node_out;

    in_size = llist_size(transaction->inputs);
    out_size = llist_size(transaction->outputs);
    buf = malloc((in_size * 96) + (out_size * 32));

    for (i = 0; i < in_size; i++)
    {
        node_in = llist_get_node_at(transaction->inputs, i);
        mem_append(buf, node_in->block_hash, &pointer);
        mem_append(buf, node_in->tx_id, &pointer);
        mem_append(buf, node_in->tx_out_hash, &pointer);
    }

    for (i = 0; i < out_size; i++)
    {
        node_out = llist_get_node_at(transaction->outputs, i);
        mem_append(buf, node_out->hash, &pointer);
    }

    sha256((const int8_t *)buf, sizeof(buf), hash_buf);
    free(buf);
    return (hash_buf);
}