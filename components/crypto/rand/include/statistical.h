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
 * @brief Statistical tests for random numbers
 * @ingroup components_crypto
 * @see https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf
 * @{
 */
#ifndef STATISTICAL_H
#define STATISTICAL_H
#include <stdint.h>
#include <stddef.h>

#define GET_BIT(ARRAY, NBIT) (ARRAY[NBIT / 8] >> (NBIT % 8)) & 1

/**
 * @brief Frequency test (monobit)
 * @note 1.It is recommended that each sequence to be tested consist of a minimum of 100 bits
 * @note 2. Decision rule should be at 1% so if P-value > 0.01 then pass
 * 
 * @param [in] buff
 * @param [in] buff_size
 * @param [in] n The length of the bit string to test, if n = 0 it will perform the entire buffer.
 * @return P-value
 */
double fntest_monobit(uint8_t *buff, size_t buff_size, size_t n);

/**
 * @brief Frequency test within a block
 * @note 1. It is recommended that each sequence to be tested consist of a minimum of 100 bits.
 * @note 2. Decision rule should be at 1% so if P-value > 0.01 then pass
 * @param [in] buff
 * @param [in] buff_size
 * @param [in] M The length of each block
 * @return P-value
 */
double fntest_wblock(uint8_t *buff, size_t buff_size, int M);

/**
 * @brief Runs test
 * @note 1. It is recommended that each sequence to be tested consist of a minimum of 100 bits.
 * @note 2. Decision rule should be at 1% so if P-value > 0.01 then pass
 * @param [in] buff uint8_t buffer to check
 * @param [in] buff_size Total length of the buffer
 * @param [in] n The length of the bit string to test
 * @return P-value
 */
double fntest_runs(uint8_t *buff, size_t buff_size, size_t n);

#endif
/** @} */