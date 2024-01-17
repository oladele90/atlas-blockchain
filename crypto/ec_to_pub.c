#include "hblk_crypto.h"



uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
    const EC_POINT *public_key;
    const EC_GROUP *group;

    public_key = EC_KEY_get0_public_key(key);
    group = EC_KEY_get0_group(key);
    EC_POINT_point2buf(group, public_key, POINT_CONVERSION_UNCOMPRESSED, pub, NULL);
    return (pub);
}
