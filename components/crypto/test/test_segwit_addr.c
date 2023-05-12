#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "unity.h"

#include "helpers.h"
#include "test_segwit_addr.h"

static const char tag[] = "[crypto][segwit_addr]";

// private functions
/**
 * @brief
 * @param [out] scriptpubkey
 * @param [out] scriptpubkeylen
 * @param [in] witver
 * @param [in] witprog
 * @param [in] witprog_len
 */
static void segwit_script_pub_key(uint8_t *scriptpubkey, size_t *scriptpubkeylen, int witver,
                                  const uint8_t *witprog, size_t witprog_len);

/**
 * @brief
 * @param [in] checksum_data
 * @param [in] expected_enc
 * @return 1 = valid, 0 = not valid
 */
static int checksum_verify(checksum_vector_data_t checksum_data, bech32_encoding expected_enc);

/**
 * @brief
 * @param [in] valid_address
 * @return 1 = valid, 0 = not valid
 */
static int segwit_verify_addr_data(valid_address_data_t valid_address);

/**
 * @brief
 * @param [in] address
 * @return 1 = valid, 0 = not valid
 */
static int segwit_verify_address(const char *address);

/**
 * @brief
 * @param [in] address
 * @return 1 = valid, 0 = not valid
 */
static int seqwit_verify_invalid_enc(invalid_address_data_t invalid_address_enc);

/**
 * @brief
 * @param [in] s1
 * @param [in] s2
 * @param [in] n
 * @return 1 = equal, 0 = not equal
 */
static int _strncasecmp(const char *s1, const char *s2, size_t n);

// Test bip173 data w/ valid checksum
TEST_CASE("bip173 data w/ valid checksum", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(bip173_valid_checksum); i++) {
        ESP_LOGI("bip173_valid_checksum", "vector data [%d] ", i);
        // should returns NO errors(1)
        TEST_ASSERT_EQUAL_INT(checksum_verify(bip173_valid_checksum[i], BECH32_ENCODING_BECH32), 1);
    }
}

// Test bip350 data w/ valid checksum
TEST_CASE("bip350 data w/ valid checksum", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(bip350_valid_checksum); i++) {
        ESP_LOGI("bip350 valid_checksum", "vector data [%d]", i);
        // should returns NO errors(1)
        TEST_ASSERT_EQUAL_INT(checksum_verify(bip350_valid_checksum[i], BECH32_ENCODING_BECH32M),
                              1);
    }
}

TEST_CASE("bip173 data w/ (IN)valid checksum", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(bip173_invalid_checksum); i++) {
        ESP_LOGI("bip173_invalid_checksum", "vector data[%d]", i);

        // should returns error(0)
        TEST_ASSERT_EQUAL_INT(checksum_verify(bip173_invalid_checksum[i], BECH32_ENCODING_BECH32),
                              0);
    }
}

// test bip350 addresses w/ valid checksum
TEST_CASE("bip350 data w/ (IN)valid checksum", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(bip350_invalid_checksum); i++) {
        ESP_LOGI("bip350 [IN]valid_checksum", "vector data[%d]", i);
        // should returns error(0)
        TEST_ASSERT_EQUAL_INT(checksum_verify(bip350_invalid_checksum[i], BECH32_ENCODING_BECH32M),
                              0);
    }
}
//
// ** verify valid address data **
//
// test bip173 valid address data
TEST_CASE("bip173 valid address data", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(bip173_valid_address); i++) {
        ESP_LOGI("bip173 valid", "address data[%d]", i);
        // 1 if ok, 0 on errors
        TEST_ASSERT_EQUAL_INT(segwit_verify_addr_data(bip173_valid_address[i]), 1);
    }
}
// test bip350 valid address data
TEST_CASE("bip350 valid address data", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(bip350_valid_address); i++) {
        ESP_LOGI("bip350 valid", "address data[%d]", i);
        TEST_ASSERT_EQUAL_INT(segwit_verify_addr_data(bip350_valid_address[i]), 1);
    }
}
//
// ** verify (IN)valid addresses **
//
// test bip173 (IN)valid addresses
TEST_CASE("bip173 (IN)valid addresses", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(bip173_invalid_address); i++) {
        ESP_LOGI("bip173 address", "[IN]valid [%d] %s", i, bip173_invalid_address[i]);
        TEST_ASSERT_EQUAL_INT(segwit_verify_address(bip173_invalid_address[i]), 0);
    }
}
// test bip350 (IN)valid addresses
TEST_CASE("bip350 (IN)valid addresses", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(bip350_invalid_address); i++) {
        ESP_LOGI("bip350 address", "[IN]valid [%d] %s", i, bip350_invalid_address[i]);
        TEST_ASSERT_EQUAL_INT(segwit_verify_address(bip350_invalid_address[i]), 0);
    }
}

TEST_CASE("Invalid enc addresses", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(invalid_address_enc); i++) {
        ESP_LOGI("address enc.", "[IN]valid [%d] %s", i, invalid_address_enc[i].hrp);
        TEST_ASSERT_EQUAL_INT(seqwit_verify_invalid_enc(invalid_address_enc[i]), 0);
    }
}

static void segwit_script_pub_key(uint8_t *scriptpubkey, size_t *scriptpubkeylen, int witver,
                                  const uint8_t *witprog, size_t witprog_len) {
    scriptpubkey[0] = witver ? (0x50 + witver) : 0;
    scriptpubkey[1] = witprog_len;
    memcpy(scriptpubkey + 2, witprog, witprog_len);
    *scriptpubkeylen = witprog_len + 2;
}

static int segwit_verify_addr_data(valid_address_data_t valid_address) {
    uint8_t witprog[40];
    size_t witprog_len;
    int witver;
    const char *hrp = "bc";
    if (memcmp(valid_address.address, "tb1", 3) == 0) {
        hrp = "tb";
    }
    uint8_t scriptpubkey[42];
    size_t scriptpubkey_len;
    char rebuild[93];

    int ret = segwit_addr_decode(&witver, witprog, &witprog_len, hrp, valid_address.address);
    // non 1  = error
    // 1      = no error
    if (ret != 1) {
        return 0;
    }

    segwit_script_pub_key(scriptpubkey, &scriptpubkey_len, witver, witprog, witprog_len);

    // if not equal length should return 1 (not valid)
    if (scriptpubkey_len != valid_address.scriptPubKeyLen) {
        return 0;
    }
    // should be 0 if are equal
    if (memcmp(scriptpubkey, valid_address.scriptPubKey, scriptpubkey_len) != 0) {
        return 0;
    }
    // 1 if ok, 0 on errors
    if (segwit_addr_encode(rebuild, hrp, witver, witprog, witprog_len) != 1) {
        return 0;
    }
    // 0 if ok, 1 on errors
    if (_strncasecmp(valid_address.address, rebuild, 93) != 0) {
        return 0;
    }
    // return: is valid address data (1)
    return 1;
};

// return 1 if valid address, other = error
static int segwit_verify_address(const char *address) {
    uint8_t witprog[40];
    size_t witprog_len;
    int witver;

    // 1 if ok
    int ret = segwit_addr_decode(&witver, witprog, &witprog_len, "bc", address);
    if (ret != 1) {
        return 0;
    }

    // 1 if ok
    ret = segwit_addr_decode(&witver, witprog, &witprog_len, "tb", address);
    if (ret != 1) {
        return 0;
    }

    // return is valid address (1)
    return 1;
}

static int checksum_verify(checksum_vector_data_t checksum_data, bech32_encoding expected_enc) {
    uint8_t data[82];
    char hrp[84];
    size_t data_len;

    bech32_encoding res = bech32_decode(hrp, data, &data_len, checksum_data.str);
    if (res != expected_enc) {
        return 0;
    }
    // the following check makes only sense for valid addresses
    char rebuild[92];

    int resi = bech32_encode(rebuild, hrp, data, data_len, checksum_data.spec);
    // 0 = error, 1 = no error
    if (resi != 1) {
        return 0;
    }

    int comp = _strncasecmp(rebuild, checksum_data.str, 92);
    // 0 = no error, others = error
    if (comp != 0) {
        return 0;
    }
    // test pass
    return 1;
}
static int seqwit_verify_invalid_enc(invalid_address_data_t invalid_address_enc) {
    char rebuild[93];
    static const uint8_t program[42] = {0};

    return segwit_addr_encode(rebuild, invalid_address_enc.hrp, invalid_address_enc.version,
                              program, invalid_address_enc.program_length);
}

static int _strncasecmp(const char *s1, const char *s2, size_t n) {
    size_t i = 0;
    while (i < n) {
        char c1 = s1[i];
        char c2 = s2[i];
        if (c1 >= 'A' && c1 <= 'Z')
            c1 = (c1 - 'A') + 'a';
        if (c2 >= 'A' && c2 <= 'Z')
            c2 = (c2 - 'A') + 'a';
        if (c1 < c2)
            return -1;
        if (c1 > c2)
            return 1;
        if (c1 == 0)
            return 0;
        ++i;
    }
    return 0;
}
