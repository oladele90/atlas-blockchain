#include "transaction.h"

/**
 * transaction_destroy - destroys transaction
 * @transaction: transaction to destroy
*/
void transaction_destroy(transaction_t *transaction)
{
	llist_destroy(transaction->inputs, 1, free);
	llist_destroy(transaction->outputs, 1, free);
	free(transaction);
}
