#include "hblk_crypto.h"

/**
 * ec_to_pub - extracts the public key from an EC_KEY structure
 * @key: pointer to the EC_KEY structure
 * @pub: buffer to store the public key
 *
 * Return: a pointer to the extracted public key (pub) or NULL on failure
 */

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	BN_CTX *ctx;
	const EC_POINT *public_key;
	const EC_GROUP *group;

	if (!key)
		return (NULL);
	ctx = BN_CTX_new();
	public_key = EC_KEY_get0_public_key(key);
	group = EC_KEY_get0_group(key);
	EC_POINT_point2oct(group, public_key,
						POINT_CONVERSION_UNCOMPRESSED, pub, EC_PUB_LEN, ctx);
	/*BN_CTX_free(ctx);*/
	return (pub);
}
