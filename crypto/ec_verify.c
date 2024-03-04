#include "hblk_crypto.h"

/**
 * ec_verify - Verify a set of bytes using an EC_KEY public key and signature
 * @key: Pointer to the EC_KEY structure containing the public key
 * @msg: Pointer to the message to be verified
 * @msglen: Length of the message
 * @sig: Pointer to the structure containing the signature
 *
 * Return: 1 if the signature is valid, 0 otherwise
 */

int ec_verify(EC_KEY const *key, uint8_t const *msg,
			  size_t msglen, sig_t const *sig)
{
	if (!key || !msg || !sig)
		return (0);
	if (ECDSA_verify(0, msg, msglen, sig->sig, sig->len, (EC_KEY *)key) == 1)
		return (1);
	return (0);
}
