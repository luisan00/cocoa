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
//
uint8_t buff[64] = {0};
//

TEST_CASE("0. Get a bunch of random bits", tag) {
    uint8_t cpy_buff[sizeof(buff)];
    memcpy(cpy_buff, buff, sizeof(buff));

    random_buffer(buff, sizeof(buff));
    // compare cpy and actual
    TEST_ASSERT_EQUAL_INT(equal_u8_array(cpy_buff, buff, sizeof(buff)), false);
}

TEST_CASE("1. Frequency test monobit", tag) {
    double mbit = ft_monobit(buff, sizeof(buff));
    double dlvl = 0.01; // 1%

    if (mbit < 0.01) {
        loge("Test Warning: %f is less than %f", mbit, dlvl);
        loge("According to 'Frequency (Monobit) Test' from NIST publ. 800-22");
        loge("This sequence of bits IS NOT random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", mbit, dlvl);
        logi("This sequence bits IS random");
        TEST_PASS();
    }
}

TEST_CASE("2. Frequency test within a block", tag) {
    double dist = ft_wblock(buff, sizeof(buff), 8);
    double dlvl = 0.01; // 1%
    if (dist < 0.01) {
        loge("Test Warning: %f is less than %f", dist, dlvl);
        loge("According to 'Frequency Test within a Block' from NIST publ. 800-22");
        loge("This sequence of bits IS NOT random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", dist, dlvl);
        logi("This sequence bits IS random");
        TEST_PASS();
    }
}
