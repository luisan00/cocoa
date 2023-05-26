/*
 * Copyright (c) 2023 Luis A. Ruiz <luisan00@hotmail.com>
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
 * @ingroup components_storage
 * @{
 * @brief Test for the storage component
 * @author  Luis A. Ruiz <luisan00@hotmail.com>
 *
 * @details Step by step for this bunch of tests
 *
 * 1.- Init nvs
 * 2.- get statistics
 * 3.- save (should WORK)
 *      3.1.- save all u8
 *      3.2.- save all u32
 *      3.3-- save all string
 *      3.4.- save all blob
 * 4.- read (should WORK)
 *      4.1.- read all u8
 *      4.2.- read all u32
 *      4.3.- read all string
 *      4.4.- read all blob
 * 5.- delete (should WORK)
 *      5.1.- delete one u8
 *      5.2.- delete one u32
 *      5.3.- delete one string
 *      5.4.- delete one blob
 * 6.- delete (should FAIL)
 *      6.1.- delete one u8
 *      6.2.- delete one u32
 *      6.3.- delete one string
 *      6.4.- delete one blob
 * 7.- get statistics
 * 8.- delete all
 * 9.- erase partition
 */
#ifndef TEST_STORAGE_H
#define TEST_STORAGE_H
#include <stdint.h>

/**
 * @brief uint8_t key/value structure for unit-tests
 * @{
 */
typedef struct {
    const char *key;
    uint8_t value;
} kv_u8_t;
/** @} */

/**
 * @brief uint32_t key/value structure for unit-tests
 * @{
 */
typedef struct {
    const char *key;
    uint32_t value;
} kv_u32_t;
/** @} */

/**
 * @brief c-string key/value structure for unit-tests
 * @{
 */
typedef struct {
    const char *key;
    const char *value;
} kv_str_t;
/** @} */

/**
 * @brief blob key/value structure, [value] is an hexstring and must to be converted an uint8_t
 * array like
 * @{
 */
typedef struct {
    const char *key;
    const char *value;
} kv_blob_t;
/** @} */

/**
 * @brief array of 8 bit integers
 */
static kv_u8_t u8_data[] = {
    {"u8_a", 0x00},
    {"u8_b", 0x01},
    {"u8_c", 0x02},
    {"u8_d", 0x03},
};
/**
 * @brief array of 32 bit integers
 */
static kv_u32_t u32_data[] = {
    {"u32_a", 0x10000000},
    {"u32_b", 0x01000001},
    {"u32_c", 0x00100002},
    {"u32_d", 0x00010003},
};
/**
 * @brief array of strings
 */
static kv_str_t str_data[] = {
    {"str_a", "abcdef0123458789abcdef0123456789abcdef0123458789abcdef0123456789abcdef"},
    {"str_b", "bcdef0123456789abcdef0123456789abcdef0123456789abc"},
    {"str_c", "cdef0123456789abcdef0123456789abcdef0123456789"},
    {"str_d", "def0123456789abcdef0123456789abcdef0123456789"},
};
/**
 * @brief array of blobs
 */
static kv_blob_t blob_data[] = {
    {
        "blob_a",
        "0a0b0c0d0e0f",
    },
    {
        "blob_b",
        "0b0c0d0e0f0a",
    },
    {
        "blob_c",
        "0c0d0e0f0a0b",
    },
    {
        "blob_d",
        "0d0e0f0a0b0c",
    },
};

#endif
/** @} */