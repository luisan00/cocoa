/**
 *
 */

#ifndef HELPERS_H
#define HELPERS_H

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C"
{
#endif
    bool check_halfshare(unsigned char *hash);
    bool check_share(unsigned char *hash);
    bool check_valid(unsigned char *hash, unsigned char *target);

    /**
     * @brief from char to uint8_t hex format.
     * @param [in] ch
     * @return
     */
    uint8_t hex(char ch);

    /**
     * @brief
     * @param [in] in
     * @param [in] in_size
     * @param [out] out
     * @return
     */
    size_t to_byte_array(const char *in, size_t in_size, uint8_t *out);
#ifdef __cplusplus
}
#endif

#endif /* HELPERS_H */