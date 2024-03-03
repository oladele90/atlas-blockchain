#include "hblk_crypto.h"

/**
 * ec_sign - Sign a given set of bytes using an EC_KEY private key
 * @key: Pointer to the EC_KEY structure containing the private key
 * @msg: Pointer to the message to be signed
 * @msglen: Length of the message
 * @sig: Pointer to the structure where the signature will be stored
 *
 * Return: Pointer to the signature buffer upon success, NULL on failure
 */

uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
								 size_t msglen, sig_t *sig)
{
	u_int32_t slen = 0;

	if (!msg || !key)
		return (NULL);
	if (ECDSA_sign(0, msg, msglen, sig->sig, &slen, (EC_KEY *)key))
	{
		sig->len = slen;
		return (sig->sig);
	}
	return (NULL);
}
