#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "esp_log.h"
#include "unity.h"

#include "base58.h"

#include "test_base58_vectors.h"
#include "helpers.h"

static const char tag[] = "[crypto][base58]";

/**
 * @brief
 * @param str
 * @return
 */
static const char *str_info(const char *str);

/**
 * @brief Encode from bytes to b58 string ~ @note [test private function]
 * @param [in] in struct containing hex string and b58 string
 * @return 1 if b58 is the same, 0 not the same
 *
 */
static int _b58_encode(base58_vector_t in);

/**
 * @brief Eecode a b58 string to bytes ~ @note [test private function]
 * @param [in] in struct containing hex string and b58 string
 * @return 1 if bytes are the same, 0 not the same
 */
static int _b58_decode(base58_vector_t in);

static int verify_b58_encode(base58_vector_t in);
static int verify_b58_decode(base58_vector_t in);

// test private functions
TEST_CASE("Test base58 encode", tag)
{
    for (size_t i = 0; i < ARRAY_SIZEOF(base58_vectors); i++)
    {
        TEST_ASSERT_EQUAL_INT(_b58_encode(base58_vectors[i]), 1);
        ESP_LOGI(tag, "base58 encode [%d]", i);
    }
}
// test private functions
TEST_CASE("Test base58 decode", tag)
{
    for (size_t i = 0; i < ARRAY_SIZEOF(base58_vectors); i++)
    {
        TEST_ASSERT_EQUAL_INT(_b58_decode(base58_vectors[i]), 1);
        ESP_LOGI(tag, "base58 decode [%d]", i);
    }
}

// public function
TEST_CASE("Test base58 encode check", tag)
{
    for (size_t i = 0; i < ARRAY_SIZEOF(check_base58_vectors); i++)
    {
        TEST_ASSERT_EQUAL_INT(verify_b58_encode(check_base58_vectors[i]), 1);
        ESP_LOGI(tag, "verify base58 [EN]code [%d] %s", i, str_info(check_base58_vectors[i].hex));
    }
}

// public function
TEST_CASE("Test base58 decode check", tag)
{
    for (size_t i = 0; i < ARRAY_SIZEOF(check_base58_vectors); i++)
    {
        TEST_ASSERT_EQUAL_INT(verify_b58_decode(check_base58_vectors[i]), 1);
        ESP_LOGI("_", "verify base58 [DE]code [%d] %s", i, str_info(check_base58_vectors[i].b58));
    }
}

static int _b58_encode(base58_vector_t in)
{
    char *str = (char *)malloc(__MAX_STR_SIZE__);
    size_t str_size = __MAX_STR_SIZE__;

    // param size will return the length that str should be
    int res = b58enc(str, &str_size, fromhex(in.hex), strlen(in.hex) / 2);
    // 0, error, 1 continue
    if (res == 0)
    {
        free(str);
        return 0;
    }
    // len of str should be equal to [size] bytes
    str = (char *)realloc(str, str_size);
    // should write [size] bytes to str
    b58enc(str, &str_size, fromhex(in.hex), strlen(in.hex) / 2);
    // check if both strings are the same
    if (equal_char_array(in.b58, str, strlen(in.b58) + 1) != 1)
    {
        free(str);
        return 0;
    }
    free(str);
    return 1;
}
static int _b58_decode(base58_vector_t in)
{
    uint8_t *buff = (uint8_t *)malloc(strlen(in.b58));
    size_t buff_size = strlen(in.b58);

    b58tobin(buff, &buff_size, in.b58);

    uint8_t bin[buff_size];

    memcpy(bin, slice_u8(buff, strlen(in.b58) - buff_size, buff_size), sizeof(bin));

    free(buff);

    return equal_char_array(in.hex, tohex(bin, sizeof(bin)), strlen(in.hex));
}

static int verify_b58_encode(base58_vector_t in)
{

    char *str = (char *)malloc(__MAX_STR_SIZE__ * sizeof(char));

    int res = base58_encode_check(fromhex(in.hex), strlen(in.hex) / 2, HASHER_SHA2D, str, __MAX_STR_SIZE__);
    // Compare length
    if (res != strlen(in.b58) + 1)
    {
        free(str);
        return 0;
    }
    str = (char *)realloc(str, res);

    // compare strings
    if (equal_char_array(in.b58, str, strlen(in.b58)) != 1)
    {
        free(str);
        return 0;
    }
    return 1;
}

static int verify_b58_decode(base58_vector_t in)
{
    uint8_t *data = malloc(strlen(in.b58) * 2);

    int res = base58_decode_check(in.b58, HASHER_SHA2D, data, strlen(in.b58) * 2 + 1);

    if (res == 0)
    {
        free(data);
        return 0;
    }

    data = realloc(data, res);

    // verify length
    if (res != base58_decode_check(in.b58, HASHER_SHA2D, data, res))
    {
        free(data);
        return 0;
    }

    // verify if both strings are the same
    if (equal_char_array(in.hex, tohex(data, res), res * 2) == 0)
    {
        free(data);
        return 0;
    }

    free(data);
    return 1;
}

static const char *str_info(const char *str)
{
    char buff[12 + 8UL];
    size_t out_sz = strlen(str);
    sprintf(buff, "%c%c%c%c...%c%c%c%c", str[0], str[1], str[2], str[3], str[out_sz - 4], str[out_sz - 3], str[out_sz - 2], str[out_sz - 1]);
    const char *out = (const char *)buff;
    return out;
}
