/**
 * Copyright (c) 2023 luisan00 <luisan00@hotmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @brief   Block utilities
 * @author  luisan00 <luisan00@hotmail.com>
 * @ingroup blocks
 * @{
 */

#ifndef BLOCKS_H
#define BLOCKS_H
#include <stdint.h>

/**
 * @brief define a block header
 */
typedef struct block_header_t {
    int32_t version;           /*!> little....4 bytes */
    uint8_t previous_hash[32]; /*!> internal.32   "   */
    uint8_t merkle_root[32];   /*!> internal.32   "   */
    uint32_t time;             /*!> little....4   "   */
    uint32_t bits;             /*!> little....4   "   */
    uint32_t nonce;            /*!> little....4   "   */
} block_header_t;              /*!> TOTAL....80 bytes */

/**
 * @brief define the size of some variables used in this component
 */
#define BLOCK_HEADER_SIZE sizeof(block_header_t) /*!> Size of block header */
#define __sizeof_sha2 32                         /*!> Size of sha2 hash */
#define __sizeof_previous_hash __sizeof_sha2     /*!> Size of previous block hash */
#define __sizeof_merkle_root __sizeof_sha2       /*!> Size of merkle root */

/**
 * @brief Get the block verion from the given block header, using bytes 0 ~ 3
 * @param [in] header_block
 * @param [out] version
 */
void get_block_version(uint8_t *header_block, int32_t *version);

/**
 * @brief Get the previous block hash from current block header, using bytes 4 ~ 35
 * @param [in] header_block
 * @param [out] previous_hash_block
 */
void get_previous_block_hash(uint8_t *header_block, uint8_t *previous_block_hash);

/**
 * @brief Get the merkle root from the given block header, bytes range 36 ~ 67
 * @param [in] header_block
 * @param [out] merkle_root
 */
void get_merkle_root(uint8_t *header_block, uint8_t *merkle_root);

/**
 * @brief get the block time from the given block header, bytes range 68 ~ 71
 * @param [in] header_block
 * @param [out] block_time
 */
void get_block_time(uint8_t *header_block, uint32_t *block_time);

/**
 * @brief get the block bits from the given block header, bytes range 72 ~ 75
 * @param [in] header_block
 * @param [out] block_bits
 */
void get_block_bits(uint8_t *header_block, uint32_t *block_bits);

/**
 * @brief get the block nonce from the given block header, bytes range 76 ~ 79
 * @param [in] header_block
 * @param [out] block_nonce
 */
void get_block_nonce(uint8_t *header_block, uint32_t *block_nonce);

#endif /* BLOCKS_H */
/** @} */
