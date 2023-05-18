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

uint8_t buff[] = {0x59, 0xff};
size_t buff_size = sizeof(buff);
//

TEST_CASE("0. Get a bunch of random bits", tag) {
    // uint8_t cpy_buff[buff_size];
    // memcpy(cpy_buff, buff, buff_size);
    // random_buffer(buff, buff_size);
    // TEST_ASSERT_EQUAL_INT(equal_u8_array(cpy_buff, buff, sizeof(buff)), false);
}

TEST_CASE("1. Frequency test monobit", tag) {
    double p_value = fntest_monobit(buff, sizeof(buff));
    double d_rule = 0.01; // 1%

    if (p_value < d_rule) {
        loge("Test Warning: %f is less than %f", p_value, d_rule);
        loge("According to 'Frequency (Monobit) Test' from NIST publ. 800-22");
        loge("This sequence of bits IS NOT random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", p_value, d_rule);
        logi("This sequence bits IS random");
        TEST_PASS();
    }
}

TEST_CASE("2. Frequency test within a block", tag) {
    double p_value = fntest_wblock(buff, sizeof(buff), 8);
    double d_rule = 0.01; // 1%
    if (p_value < d_rule) {
        loge("Test Warning: %f is less than %f", p_value, d_rule);
        loge("According to 'Frequency Test within a Block' from NIST publ. 800-22");
        loge("This sequence of bits IS NOT random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", p_value, d_rule);
        logi("This sequence bits IS random");
        TEST_PASS();
    }
}

TEST_CASE("3. Runs test", tag) {
    double p_value = fntest_runs(buff, buff_size);
    double d_rule = 0.01; // decision rule at 1%
    if (p_value < d_rule) {
        loge("Test Warning: %f is less than %f", p_value, d_rule);
        loge("According to 'Runs Test' from NIST publ. 800-22");
        loge("This sequence of bits IS NOT random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", p_value, d_rule);
        logi("This sequence bits IS random");
        TEST_PASS();
    }
}
