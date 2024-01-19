#include "hblk_crypto.h"

/**
 * ec_save - Save EC key pair to files in the specified folder.
 * @key: The EC key pair to be saved.
 * @folder: The folder in which to save the key pair files.
 *
 * Return: 1 on success, 0 on failure.
 */

int ec_save(EC_KEY *key, char const *folder)
{
	FILE *fdpub, *fdpri;
	struct stat st = {0};

	char *pubpath = calloc(strlen(folder) + strlen(PUB_FILENAME) + 1, 1);
	char *pripath = calloc(strlen(folder) + strlen(PRI_FILENAME) + 1, 1);

	sprintf(pubpath, "%s/%s", folder, PUB_FILENAME);
	sprintf(pripath, "%s/%s", folder, PRI_FILENAME);

	if (stat(folder, &st) != 0)
		mkdir(folder, 0777);

	fdpub = fopen(pubpath, "w");
	fdpri = fopen(pripath, "w");

	PEM_write_EC_PUBKEY(fdpub, key);
	PEM_write_ECPrivateKey(fdpri, key, NULL, NULL, 0, NULL, NULL);

	fclose(fdpub);
	fclose(fdpri);

	free(pubpath);
	free(pripath);

	return (1);
}
