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
uint8_t buff[3] = {0};
//
TEST_CASE("1. Frequency test monobit", tag) {
    // uint8_t buff[32] = {0}; // 32 * 8 = 256 bits
    random_buffer(buff, sizeof(buff));
    double mbit = ft_monobit(buff, sizeof(buff));
    double dlvl = 0.01; // 1%

    if (mbit < 0.01) {
        loge("Test Warning: %f is less than %f", mbit, dlvl);
        loge("According to 'Frequency (Monobit) Test'  from "
             "https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf");
        loge("This sequence of bits IS NOT random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", mbit, dlvl);
        logi("This sequence bits IS random");
    }
}

TEST_CASE("2. Frequency test within a block", tag) {
    // uint8_t buff[3] = {0}; // 32 * 8 = 256 bit
    // random_buffer(buff, sizeof(buff));
    // uint8_t buff[]={0x10, 0x50, 0xf0};
    double dist = ft_wblock(buff, sizeof(buff), 8);
    double dlvl = 0.01; // 1%
    if (dist < 0.01) {
        loge("Test Warning: %f is less than %f", dist, dlvl);
        loge("According to 'Frequency Test within a Block'  from "
             "https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf");
        loge("This sequence of bits IS NOT random");
        TEST_FAIL();
    } else {
        logi("Test Success: %f is bigger than %f", dist, dlvl);
        logi("This sequence bits IS random");
    }
}
