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
 * @brief   Common and Helpers utils.
 * @author  luisan00 <luisan00@hotmail.com>
 * @ingroup helpers
 * @{
 */

#ifndef HELPERS_H
#define HELPERS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
/**
 * @brief count elements on different array types
 */
#define ARRAY_SIZEOF(x) sizeof(x) / sizeof(x[0])

/**
 * @brief
 */
#define FROMHEX_MAXLEN 512
/**
 * @brief from const char to uint8_t array of  1 "one" element
 */
uint8_t from_char(const char *in);

/**
 * @brief from const char array to uint8_t array
 */
uint8_t *from_char_array(const char *in, size_t out_len);

/**
 * @brief u8_to_char
 */
char *from_u8(uint8_t in);

/**
 * @brief
 */
void from_u8_array(uint8_t *in, size_t in_size, char *out, size_t out_size);

/**
 * @brief   Get a slice of [len] elements from position [pos]
 *          on the given array [arr] and return it.
 */
uint8_t *slice_u8(uint8_t *arr, int pos, size_t len);

/**
 * @brief flip the given array [buff] and return it.
 */
uint8_t *flip_u8(uint8_t *buff, size_t buff_size);

/**
 * @brief
 */
const uint8_t *fromhex(const char *str);

/**
 * @brief
 */
const char *tohex(uint8_t *in, size_t in_size);

/**
 * @brief Compare if two uint8_t values are equal
 */
bool equal_u8(const uint8_t byte1, const uint8_t byte2);

/**
 * @brief Compare if two uint8_t arrays of the same size [size] are equal 
 */
bool equal_u8_array(const uint8_t *arr_1, const uint8_t *arr_2, size_t size);

/**
 * @brief Compare if two char are equal
 */
bool equal_char(char _c1, char _c2);

/**
 * @brief
 */
bool equal_char_array(const char *_s1, const char *_s2, size_t _len);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* HELPERS_H */
/** @} */
