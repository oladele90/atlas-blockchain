#include "blockchain.h"

/**
 * hash_matches_difficulty - Check if a hash meets a certain difficulty.
 * @hash: The hash to check.
 * @difficulty: The difficulty level to match.
 *
 * Return: 1 if the hash meets the difficulty level, 0 otherwise.
 */

int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
							uint32_t difficulty)
{
	int i, j;
	uint32_t count = 0;
	uint8_t bit;

	for (i = 0; i <= SHA256_DIGEST_LENGTH; i++)
	{
		for (j = 7; j >= 0; j--)
		{
			bit = (hash[i] >> j);
			if (bit == 0)
				count++;
			else
				return (count >= difficulty ? 1 : 0);
		}
	}

	return (count >= difficulty ? 1 : 0);
}
