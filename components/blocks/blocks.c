#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"
#include "blocks.h"

void get_block_version(uint8_t *header_block, int32_t *version)
{
    int32_t _v = (int32_t)(header_block[0] | (header_block[1] << 8) | (header_block[2] << 16) | (header_block[3] << 24));
    memcpy(version, &_v, sizeof(int32_t));
}

void get_previous_block_hash(uint8_t *header_block, uint8_t *previous_block_hash)
{
    uint8_t *buff = slice_u8(header_block, 4, __sizeof_previous_hash);
    uint8_t *flipped_buff = flip_u8(buff, __sizeof_previous_hash);
    memcpy(previous_block_hash, flipped_buff, __sizeof_merkle_root);
}

void get_merkle_root(uint8_t *header_block, uint8_t *merkle_root)
{
    uint8_t *buff = slice_u8(header_block, 36, __sizeof_merkle_root);
    uint8_t *flipped_buff = flip_u8(buff, __sizeof_merkle_root);
    memcpy(merkle_root, flipped_buff, __sizeof_merkle_root);
}

void get_block_time(uint8_t *header_block, uint32_t *block_time)
{
    uint32_t _time = (uint32_t)(header_block[68] | (header_block[69] << 8) | (header_block[70] << 16) | (header_block[71] << 24));
    memcpy(block_time, &_time, sizeof(uint32_t));
}

void get_block_bits(uint8_t *header_block, uint32_t *block_bits)
{
    uint32_t _bits = (uint32_t)(header_block[72] | (header_block[73] << 8) | (header_block[74] << 16) | (header_block[75] << 24));
    memcpy(block_bits, &_bits, sizeof(uint32_t));
}

void get_block_nonce(uint8_t *header_block, uint32_t *block_nonce)
{
    uint32_t _nonce = (uint32_t)(header_block[76] | (header_block[77] << 8) | (header_block[78] << 16) | (header_block[79] << 24));
    memcpy(block_nonce, &_nonce, sizeof(uint32_t));
}