#include "hblk_crypto.h"

/**
 * sha256 - Computes the SHA-256 hash of a sequence of bytes
 * @s: Sequence of bytes to be hashed
 * @len: Number of bytes to hash in s
 * @digest: Array to store the resulting hash
 *
 * Return: Pointer to the digest or NULL if digest is NULL
 */

uint8_t *sha256(int8_t const *s, size_t len,
				uint8_t digest[SHA256_DIGEST_LENGTH])
{
	SHA256_CTX hash;

	if (digest == NULL)
		return (NULL);

	SHA256_Init(&hash);
	SHA256_Update(&hash, s, len);
	SHA256_Final(digest, &hash);

	return (digest);
}
