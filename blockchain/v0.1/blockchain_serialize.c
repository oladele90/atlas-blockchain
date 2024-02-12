#include "blockchain.h"

/**
 * writer - Callback function to write block data to file
 * @node: Current node being iterated over
 * @idx: Index of the current node
 * @arg: Pointer to the file descriptor
 *
 * Return: 0 on success, non-zero on failure
 */

int writer(llist_node_t node, unsigned int idx, void *arg)
{
    FILE *fd = (FILE *)arg;
    block_t *block = node;

    (void)(idx);
    fwrite(&block->info, sizeof(block->info), 1, fd);
    fwrite(&block->data.len, sizeof(block->data.len), 1, fd);
	fwrite(&block->data.buffer, block->data.len, 1, fd);
	fwrite(&block->hash, sizeof(block->hash), 1, fd);
    return (0);

}

/**
 * blockchain_serialize - Serialize a blockchain and write it to a file
 * @blockchain: Pointer to the blockchain to be serialized
 * @path: Path to the file where the serialized blockchain will be written
 *
 * Return: 1 on success, 0 on failure
 */

int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
    FILE *fd;
    header_t new_header;

    fd = fopen(path, "w");
    memcpy(&new_header.magic, "HBLK", 4);
    memcpy(new_header.version, "0.1", 3);
    new_header.endian = _get_endianness();
    new_header.blocks = (uint32_t)llist_size(blockchain->chain);
    fwrite(&new_header, sizeof(new_header), 1, fd);
    llist_for_each(blockchain->chain, writer, fd);
    fclose(fd);
    return (1);
}