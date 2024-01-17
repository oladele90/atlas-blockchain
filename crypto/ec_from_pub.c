#include "hblk_crypto.h"

/**
 * ec_from_pub - creates an EC_KEY structure given a public key
 * @pub: pointer to the public key buffer
 *
 * Return: a pointer to the created EC_KEY structure or NULL on failure
 */

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	BN_CTX *ctx;
	EC_KEY *key;
	const EC_POINT *p;
	const EC_GROUP *group;

	if (!pub)
		return (NULL);
	ctx = BN_CTX_new();
	key = EC_KEY_new_by_curve_name(EC_CURVE);
	group = EC_KEY_get0_group(key);
	p = EC_POINT_new(group);
	EC_POINT_oct2point(group, (EC_POINT *)p, pub, EC_PUB_LEN, ctx);
	EC_KEY_set_public_key(key, p);
	BN_CTX_free(ctx);
	EC_POINT_clear_free((EC_POINT *)p);
	return (key);
}
