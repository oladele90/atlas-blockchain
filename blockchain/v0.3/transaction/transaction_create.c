#include "transaction.h"

transaction_t *transaction_create(EC_KEY const *sender,
    EC_KEY const *receiver, uint32_t amount,
    llist_t *all_unspent)
{
    int i, list_size;
    unspent_tx_out_t *sender_unspent_tx;
    tx_in_t *sender_in;
    uint8_t pub[EC_PUB_LEN];
    uint32_t sender_amount = 0;

    transaction_t *new_t = calloc(sizeof(transaction_t), 1);

    new_t->outputs = llist_create(MT_SUPPORT_TRUE);
    new_t->inputs = llist_create(MT_SUPPORT_TRUE);
    list_size = llist_size(all_unspent);
    for (i = 0; i < list_size; i++)
    {
        sender_unspent_tx = llist_get_node_at(all_unspent, i);
        ec_to_pub(sender, pub);
        if (!memcmp(&pub, &sender_unspent_tx->out.pub, EC_PUB_LEN))
        {
            sender_amount += sender_unspent_tx->out.amount;
            llist_add_node(new_t->inputs, tx_in_create(sender_unspent_tx), ADD_NODE_REAR);
        }
    }
    if (amount > sender_amount)
        return (NULL);
    ec_to_pub(receiver, pub);
    llist_add_node(new_t->outputs, tx_out_create(amount, pub), ADD_NODE_REAR);
    if (amount != sender_amount)
    {
        ec_to_pub(sender, pub);
        llist_add_node(new_t->outputs, tx_out_create(sender_amount - amount, pub), ADD_NODE_REAR);
    }
    transaction_hash(new_t, new_t->id);
    for (i = 0; i < llist_size(new_t->inputs); i++)
    {
        sender_in = llist_get_node_at(new_t->inputs, i);
        sender_in->sig = *tx_in_sign(sender_in, new_t->id, sender, all_unspent);
    }
    return (new_t);

}