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
 * @ingroup storage
 * @{
 * @brief
 * @author  Luis A. Ruiz <luisan00@hotmail.com>
 */
#ifndef TEST_STORAGE_H
#define TEST_STORAGE_H
#include <stdint.h>

typedef struct
{
    const char *key;
    uint8_t value;
} kv_u8_t;

typedef struct
{
    const char *key;
    uint32_t value;
} kv_u32_t;

typedef struct
{
    const char *key;
    const char *value;
} kv_str_t;

static kv_u8_t u8_data[] = {
    {"u8_a", 0x00},
    {"u8_b", 0x01},
    {"u8_c", 0x02},
    {"u8_d", 0x03},
};

static kv_u32_t u32_data[] = {
    {"u32_a", 0x10000000},
    {"u32_b", 0x01000001},
    {"u32_c", 0x00100002},
    {"u32_d", 0x00010003},
};

static kv_str_t str_data[] = {
    {"str_a", "abcdef0123458789abcdef0123456789"},
    {"str_b", "bcdef0123456789abcdef0123456789a"},
    {"str_c", "cdef0123456789abcdef0123456789ab"},
    {"str_d", "def0123456789abcdef0123456789abc"},
};
#endif
/** @} */