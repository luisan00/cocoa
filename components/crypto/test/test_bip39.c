#include "unity.h"
#include "helpers.h"
#include "logger.h"

#include "bip39.h"
#include "test_bip39.h"

static const char tag[] = "[crypto][bip39]";

// bip39 mnemonic check
TEST_CASE("bip39 mnemonic check", tag) {

    for (size_t i = 0; i < ARRAY_SIZEOF(vectors_ok); i++) {
        printf("vector ok: %d of %d\n", i + 1, ARRAY_SIZEOF(vectors_ok));
        TEST_ASSERT_EQUAL_INT(1, mnemonic_check(vectors_ok[i]));
    }
    for (size_t i = 0; i < ARRAY_SIZEOF(vectors_fail); i++) {
        printf("vector fail: %d of %d\n", i + 1, ARRAY_SIZEOF(vectors_fail));
        TEST_ASSERT_EQUAL_INT(0, mnemonic_check(vectors_fail[i]));
    }
}

// bip39 mnemonic to bits
TEST_CASE("bip39 mnemonic to bits", tag) {

    for (size_t i = 0; i < ARRAY_SIZEOF(bip39_data); i++) {
        printf("vector: %d of %d\n", i + 1, ARRAY_SIZEOF(bip39_data));
        uint8_t mnemonic_bits[64];
        size_t bits_len = mnemonic_to_bits(bip39_data[i].mnemonic, mnemonic_bits);
        bits_len = bits_len * 4 / 33;
        // compare sizes
        TEST_ASSERT_EQUAL_INT(strlen(bip39_data[i].bits) / 2, bits_len);
        // compare bits
        TEST_ASSERT_EQUAL_UINT8_ARRAY(fromhex(bip39_data[i].bits), mnemonic_bits, bits_len);
    }
}