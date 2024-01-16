#include "hblk_crypto.h"

/**
 * ec_create - Creates a new EC key pair
 *
 * Return: Pointer to the newly created EC_KEY structure, or NULL on failure
 */

EC_KEY *ec_create(void)
{
	EC_KEY *my_ec_key;

	my_ec_key = EC_KEY_new_by_curve_name(714);
	EC_KEY_generate_key(my_ec_key);
	return (my_ec_key);
}
