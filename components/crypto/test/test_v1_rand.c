#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "logger.h"
#include "unity.h"
#include "helpers.h"
#include "rand.h"
#include "statistical.h"

static const char tag[] = "[rand]";

uint8_t buff[256] = {0};

TEST_CASE("0. Get a bunch of random bits", tag) { random_buffer(buff, sizeof(buff)); }

TEST_CASE("1. Frequency test monobit", tag) {
    double p_value = fntest_monobit(buff, sizeof(buff) * 8);
    double d_rule = 0.01; // decision rule at 1%

    if (p_value < d_rule) {
        loge("Test Warning: %f is less than %f", p_value, d_rule);
        loge("According to 'Frequency (Monobit) Test' from NIST publ. 800-22 r1a");
        loge("This sequence of bits could be not random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", p_value, d_rule);
        TEST_PASS();
    }
}

TEST_CASE("2. Frequency test within a block", tag) {
    double p_value = fntest_wblock(buff, sizeof(buff) * 8, 16);
    double d_rule = 0.01; // decision rule at 1%
    if (p_value < d_rule) {
        loge("Test Warning: %f is less than %f", p_value, d_rule);
        loge("According to 'Frequency Test within a Block' from NIST publ. 800-22 r1a");
        loge("This sequence of bits could be not random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", p_value, d_rule);
        TEST_PASS();
    }
}

TEST_CASE("3. Runs test", tag) {
    double p_value = fntest_runs(buff, sizeof(buff) * 8, 0.02);
    double d_rule = 0.01; // decision rule at 1%
    if (p_value == -1.0) {
        TEST_FAIL();
    } else if (p_value != -1.0 && p_value < d_rule) {
        loge("Test Warning: %f is less than %f", p_value, d_rule);
        loge("According to 'Runs Test' from NIST publ. 800-22 r1a");
        loge("This sequence of bits could be not random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", p_value, d_rule);
        TEST_PASS();
    }
}

TEST_CASE("4. Longest Run of Ones in a Block", tag) {
    double p_value = fntest_longest_runs(buff, sizeof(buff) * 8);
    double d_rule = 0.01; // decision rule at 1%
    if (p_value == -1.0) {
        TEST_FAIL();
    } else if (p_value != -1.0 && p_value < d_rule) {
        loge("Test Warning: %f is less than %f", p_value, d_rule);
        loge("According to 'Longest Run of Ones in a Block' from NIST publ. 800-22 r1a");
        loge("This sequence of bits could be not random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", p_value, d_rule);
        TEST_PASS();
    }
}

TEST_CASE("5. Matrix rank", tag) {
    double p_value = fntest_matrix_rank(buff, sizeof(buff) * 8, 32, 32);
    double d_rule = 0.01; // decision rule at 1%
    if (p_value < d_rule) {
        loge("Test Warning: %f is less than %f", p_value, d_rule);
        loge("According to 'Matrix rank test' from NIST publ. 800-22 r1a");
        loge("This sequence of bits could be not random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", p_value, d_rule);
        TEST_PASS();
    }
}

TEST_CASE("6. Discrete Fourier Transform (Spectral)", tag) {
    double p_value = fntest_spectral(buff, sizeof(buff) * 8);
    double d_rule = 0.01; // decision rule at 1%
    if (p_value < d_rule) {
        loge("Test Warning: %f is less than %f", p_value, d_rule);
        loge("According to 'Discrete Fourier Transform' from NIST publ. 800-22 r1a");
        loge("This sequence of bits could be not random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", p_value, d_rule);
        TEST_PASS();
    }
}