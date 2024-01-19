#include "hblk_crypto.h"

/**
 * ec_load - Load an EC key pair from the filesystem
 * @folder: Path to the folder in which the key files are stored
 *
 * Return: Pointer to the loaded EC_KEY structure, or NULL on failure
 */

EC_KEY *ec_load(char const *folder)
{
	FILE *fdpub, *fdpri;
	EC_KEY *key = EC_KEY_new_by_curve_name(NID_secp256k1);
	char *pubpath = calloc(strlen(folder) + strlen(PUB_FILENAME) + 1, 1);
	char *pripath = calloc(strlen(folder) + strlen(PRI_FILENAME) + 1, 1);

	sprintf(pubpath, "%s/%s", folder, PUB_FILENAME);
	sprintf(pripath, "%s/%s", folder, PRI_FILENAME);

	fdpub = fopen(pubpath, "r");
	fdpri = fopen(pripath, "r");

	PEM_read_EC_PUBKEY(fdpub, &key, NULL, NULL);
	PEM_read_ECPrivateKey(fdpri, &key, NULL, NULL);

	fclose(fdpub);
	fclose(fdpri);

	return (key);
}
