#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_timer.h"
#include "unity.h"

#include "helpers.h"
#include "logger.h"
#include "statistical.h"
#include "test_statistical.h"
// Tests from https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf
static const char tag[] = "[statistical]";

// monobit (I) - from section 2.1.4
TEST_CASE("Frequency test (monobit) (I)", tag) {
    int bitstr[] = {1, 0, 1, 1, 0, 1, 0, 1, 0, 1};
    uint8_t buff[] = {0xad, 0x02};
    size_t n = 10;
    // check bit string
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.527089;
    double result = fntest_monobit(buff, n);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}
// monobit (II) - from section 2.1.8
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
    double result = fntest_monobit(buff, n);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

//  Frequency test within a block (I) - from section 2.2.4
TEST_CASE("Frequency Test within a Block (I)", tag) {
    int bitstr[] = {0, 1, 1, 0, 0, 1, 1, 0, 1, 0};
    uint8_t buff[] = {0x66, 0x01};
    int M = 3;
    size_t n = 10;
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.801252;
    double result = fntest_wblock(buff, n, M);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// Frequency test within a block (II) - from section 2.2.8
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
    double result = fntest_wblock(buff, n, M);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// Runs test (I) - from section 2.3.4
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
    double result = fntest_runs(buff, n, t);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// Runs test (II) from section 2.3.8
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
    double result = fntest_runs(buff, n, t);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// Longest run of ones (I) - from section 2.3.8
TEST_CASE("Longest run of ones (I)", tag) {
    int bitstr[] = {1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1,
                    0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
                    1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1,
                    1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0,
                    1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0};

    uint8_t buff[] = {0x33, 0xa8, 0x36, 0x32, 0x07, 0x40, 0xb2, 0x8a,
                      0xc8, 0x6b, 0x01, 0xeb, 0x33, 0x67, 0x1b, 0x4d};
    int n = 128;
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.180609;
    double result = fntest_longest_runs(buff, n);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}
TEST_CASE("Binary matrix rank (I)", tag) {
    int bitstr[] = {0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1};
    uint8_t buff[] = {0x9a, 0x54, 0x0b};
    int n = 20;
    int M = 3;
    int Q = 3;
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.741948;
    double result = fntest_matrix_rank(buff, n, M, Q);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

TEST_CASE("Discrete Fourier transform test (I)", tag) {
    // 1001 0100 : 0x29
    // 1100 0000 : 0x03
    int bitstr[] = {1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0};
    uint8_t buff[] = {0x29, 0x03};
    size_t n = 10;
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.029523;
    double result = fntest_spectral(buff, n);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

TEST_CASE("Discrete Fourier transform test (II)", tag) {

    int bitstr[] = {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0,
                    1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0,
                    0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1,
                    1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};

    uint8_t buff[] = {0x93, 0xf0, 0x5b, 0x45, 0x84, 0x16, 0x43, 0x2c, 0x23, 0x63, 0x46, 0xd1, 0x01};
    size_t n = 100;
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.168669;
    double result = fntest_spectral(buff, n);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}