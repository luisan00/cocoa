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
 * @brief Statistical tests for random numbers is a series of test to check if a given sequence of
 * bits can be (or not) considered as random.
 * | Test name                             | Status |
 * |:--------------------------------------|:------:|
 * | Frequency test (monobit)              | done   |
 * | Frequency test within a block         | done   |
 * | Runs test                             | done   |
 * | Longest run of ones                   | done   |
 * | Matrix rank test                      | done   |
 * | Discrete Fourier Transform (Spectral) | done   |
 * | Non-overlapping Template Matching     | done   |
 * | Overlapping Template Matching         | not  "        |
 * | Maurer’s “Universal Statistical”      | not  "        |
 * | Linear Complexity                     | not  "        |
 * | Serial                                | not  "        |
 * | Approximate Entropy                   | not  "        |
 * | Cumulative Sums (Cusum)               | not  "        |
 * | Random Excursions Variant             | not  "        |
 *
 * @warning It is important to note that if a sequence of bits is considered valid or not after
 * passing through one or more tests, it only gives us a probability and not an absolute result
 *
 * @ref [1] A Statistical Test Suite for Random and Pseudorandom Number Generators for
 * Cryptographic Applications;
 * https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf
 *
 * @ref [2] A remark on the Discrete Fourier Transform statistical;
 * https://eprint.iacr.org/2022/066.pdf
 *
 * @ingroup components_crypto
 * @{
 */
#ifndef STATISTICAL_H
#define STATISTICAL_H
#include <stdint.h>
#include <stddef.h>


/**
 * @brief Reads the bit number (NBIT) from an array (ARRAY)
 * @param array [in]
 * @param nbit [in]
 * @return 1 or 0
 */
#define GET_BIT(arr, nbit) (arr[nbit / 8] >> (nbit % 8)) & 1

/**
 * @brief set to 1 to compute probability in the binary matrix rank test
 */
#define BMR_COMPUTE_PROBABILITY 0

/**
 * @brief set to 1 to compute probability in the non overlapping template test
 */
#define NON_OT_COMPUTE_PROBABILITY 1

/**
 * @brief Aperiodic templates: 148 => temp_length = 9
 */
#define MAX_NUMOF_TEMPLATES 148

#define ARRAY_SIZEOF(x) sizeof(x) / sizeof(x[0])

/**
 * @brief Frequency test (monobit)
 * @note 1.It is recommended that each sequence to be tested consist of a minimum of 100 bits
 * @note 2. Decision rule should be at 1% so if P-value > 0.01 then pass
 *
 * @param [in] buff
 * @param [in] n length of the bit string to test
 * @return P-value
 */
double fntest_monobit(uint8_t *buff, size_t n);

/**
 * @brief Frequency test within a block
 * @note 1. It is recommended that each sequence to be tested consist of a minimum of 100 bits.
 * @note 2. Decision rule should be at 1% so if P-value > 0.01 then pass
 * @param [in] buff
 * @param [in] n length of the bit string to test
 * @param [in] M The length of each block
 * @return P-value
 */
double fntest_wblock(uint8_t *buff, int n, int M);

/**
 * @brief Runs test
 * @note 1. It is recommended that each sequence to be tested consist of a minimum of 100 bits.
 * @note 2. Decision rule should be at 1% so if P-value > 0.01 then pass
 * @param [in] buff uint8_t buffer to check
 * @param [in] n The length of the bit string to test
 * @param [in] t thresold value
 * @return P-value
 */
double fntest_runs(uint8_t *buff, int n, double t);

/**
 * @brief Longest run of ones
 *
 * | bits   | (M) bits| (N) blocks |  K  |
 * |-------:|--------:|-----------:|:---:|
 * |    128 |       8 |         16 |  3  |
 * |   6272 |     128 |         49 |  5  |
 * | 750000 |     10⁴ |         75 |  6  |
 *
 * @param [in] buff uint8_t array of bytes to check
 * @param [in] n number of bits to check
 * @return P-value
 */
double fntest_longest_runs(uint8_t *buff, int n);

/**
 * @brief
 * @param [in] buff uint8_t array of bytes to check
 * @param [in] n    number of bits to check
 * @param [in] M    number of rows
 * @param [in] Q    number of columns
 * @return P-value
 *
 */
double fntest_matrix_rank(uint8_t *buff, int n, int M, int Q);

/**
 * @brief Discrete Fourier Transform (Spectral) Test
 *
 * @note  (*1) A remark on the Discrete Fourier Transform statistical test
 *        Authors: Asandoaiei David, Anghel Florin, Tabacaru Robert
 *        Date: January 13, 2022
 *        https://eprint.iacr.org/2022/066.pdf
 *
 * @param [in] buff uint8_t array of bytes to check
 * @param [in] n    number of bits to check
 * @return P-value
 */

double fntest_spectral(uint8_t *buff, int n);

/**
 * @brief Non-overlapping Template Matching
 * @param [in] buff uint8_t array to check
 * @param [in] n number of bits to check
 * @param [in] t pointer to a matrix containing the templates to search in the given array 
 * @param [in] m length of t
 * @param [in] N number blocks
 * @return P-value
 */
double fntest_non_overlapping_template(uint8_t *buff, size_t n, int *t, size_t m, int N);

/**
 * @brief Overlapping Template Matching
 * @param [in] buff uint8_t array to check
 * @param [in] n number of bits to check
 * @return P-value
 */
double fntest_overlapping_template(uint8_t *buff, int n);

/**
 * @brief Maurer’s “Universal Statistical”
 * @param [in] buff uint8_t array to check
 * @param [in] n number of bits to check
 * @return P-value
 */
double fntest_maurer_us(uint8_t *buff, int n);

/**
 * @brief Linear complexity
 * @param [in] buff uint8_t array to check
 * @param [in] n number of bits to check
 * @return P-value
 */
double fntest_linear_complex(uint8_t *buff, int n);

/**
 * @brief Serial test
 * @param [in] buff uint8_t array to check
 * @param [in] n number of bits to check
 * @return P-value
 */
double fntest_serial(uint8_t *buff, int n);

/**
 * @brief Approximate Entropy
 * @param [in] buff uint8_t array to check
 * @param [in] n number of bits to check
 * @return P-value
 */
double fntest_aprox_entropy(uint8_t *buff, int n);

/**
 * @brief Cumulative Sums (Cusum)
 * @param [in] buff uint8_t array to check
 * @param [in] n number of bits to check
 * @return P-value
 */
double fntest_cusum(uint8_t *buff, int n);

/**
 * @brief Random Excursions Variant
 * @param [in] buff uint8_t array to check
 * @param [in] n number of bits to check
 * @return P-value
 */
double fntest_rand_excursions(uint8_t *buff, int n);
#endif /* STATISTICAL_H */
/** @} */
