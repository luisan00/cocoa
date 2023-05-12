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

static kv_u8_t kv_u8[] = {
    {"u8a", 0x00},
    {"u8b", 0x01},
    {"u8c", 0x02},
    {"u8d", 0x03},
};

static kv_u32_t kv_u32[] = {
    {"u32a", 0x10000000},
    {"u32b", 0x01000001},
    {"u32c", 0x00100002},
    {"u32d", 0x00010003},
};

#endif
/** @} */