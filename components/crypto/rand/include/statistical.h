/**
 * @brief Statistical tests for random numbers
 * @ref https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf
 * @{
 */
#ifndef STATISTICAL_H
#define STATISTICAL_H
#include <stdint.h>
#include <stddef.h>
#define GET_BIT(ARRAY, NBIT) (ARRAY[NBIT / 8] >> (NBIT % 8)) & 1

/**
 * @brief Frequency test (monobit)
 */
double ft_monobit(uint8_t *buff, size_t buff_size);

/**
 * @brief Frequency test within a block
 * @return The incomplete gamma function for Q(a,x)
 */
double ft_wblock(uint8_t *buff, size_t buff_size, int M);


#endif
/** @} */