#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unity.h"

#include "logger.h"
#include "statistical.h"

static const char tag[] = "[statistical]";
// Tests from https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf

// monobit 1 - from section 2.1.4
TEST_CASE("Frequency test (monobit) (I)", tag) {
    int bitstr[] = {1, 0, 1, 1, 0, 1, 0, 1, 0, 1};
    uint8_t buff[] = {0xad, 0x02};
    size_t n = 10;
    // check bit string
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.527089;
    double result = fntest_monobit(buff, sizeof(buff), n);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}
// monobit 2 - from section 2.1.8
TEST_CASE("Frequency test (monobit) (II)", tag) {
    int bitstr[] = {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1,
                    0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1,
                    0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0,
                    0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0};
    uint8_t buff[] = {0x93, 0xf0, 0x5b, 0x45, 0x84, 0x16, 0x43, 0x2c, 0x23, 0x63, 0x46, 0xd1, 0x01};
    size_t n = 100;
    // check bit string
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.109599;
    double result = fntest_monobit(buff, sizeof(buff), n);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

//  Frequency test within a block - from section 2.2.4
TEST_CASE("Frequency Test within a Block (I)", tag) {
    int bitstr[] = {0, 1, 1, 0, 0, 1, 1, 0, 1, 0};
    uint8_t buff[] = {0x66, 0x01};
    int M = 3;
    size_t n = 10;
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.801252;
    double result = fntest_wblock(buff, sizeof(buff), M, n);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// Frequency test within a block - from section 2.2.8
TEST_CASE("Frequency Test within a Block (II)", tag) {

    int bitstr[] = {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1,
                    0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1,
                    0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0,
                    0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0};
    uint8_t buff[] = {0x93, 0xf0, 0x5b, 0x45, 0x84, 0x16, 0x43, 0x2c, 0x23, 0x63, 0x46, 0xd1, 0x01};
    int M = 10;
    size_t n = 100;
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.706438;
    double result = fntest_wblock(buff, sizeof(buff), M, n);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// Runs test - from section 2.3.4
TEST_CASE("Runs test (I)", tag) {
    int bitstr[] = {1, 0, 0, 1, 1, 0, 1, 0, 1, 1};
    uint8_t buff[] = {0x59, 0x03};
    size_t n = 10;
    // for this test
    // τ = 2 / sqrt(n)
    double t = 2 / sqrt(n);
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }

    double expected = 0.147232;
    double result = fntest_runs(buff, sizeof(buff), n, t);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// Runs test . from section 2.3.8
TEST_CASE("Runs test (II)", tag) {

    int bitstr[] = {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1,
                    0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1,
                    0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0,
                    0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0};
    uint8_t buff[] = {0x93, 0xf0, 0x5b, 0x45, 0x84, 0x16, 0x43, 0x2c, 0x23, 0x63, 0x46, 0xd1, 0x01};
    size_t n = 100;
    double t = 0.02;
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.500798;
    double result = fntest_runs(buff, sizeof(buff), n, t);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}
