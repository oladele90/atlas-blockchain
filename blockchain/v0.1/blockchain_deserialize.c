#include "blockchain.h"


blockchain_t *write_blocks(uint32_t size, FILE *fd, blockchain_t *chain)
{
    block_t *block;
    uint32_t i;

    for (i = 0; i < size; i++)
    {
        block = calloc(1, sizeof(block_t));
        fread(&block->info, sizeof(block_info_t), 1, fd);
        fread(&(block->data.len), sizeof(uint8_t), 4, fd);
        fread(block->data.buffer, sizeof(uint8_t), block->data.len, fd);
        fread(block->hash, sizeof(uint8_t), SHA256_DIGEST_LENGTH, fd);
        llist_add_node(chain->chain, block, ADD_NODE_REAR);
    }

    return (chain);

}

blockchain_t *blockchain_deserialize(char const *path)
{
    FILE *fd = fopen(path, "r");
    char buf[4] = {0};
    uint8_t end;
    uint32_t size;
    blockchain_t *blockchain = calloc(1, sizeof(blockchain_t));


    if (!fd)
        return (NULL);
    fread(buf, sizeof(uint8_t), 4, fd);
    fread(buf, sizeof(uint8_t), 3, fd);
    fread(&end, sizeof(uint8_t), 1, fd);
    fread(&size, sizeof(uint32_t), 1, fd);
    blockchain->chain = llist_create(MT_SUPPORT_FALSE);
    blockchain = write_blocks(size, fd, blockchain);
    fclose(fd);

    return (blockchain);
}
