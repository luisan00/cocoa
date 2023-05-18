#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unity.h"

#include "logger.h"
#include "statistical.h"

static const char tag[] = "[statistical]";

// monobit 1 - from section 2.1.4
TEST_CASE("Frequency test monobit 1", tag) {
    // buf = 1011 0101 0100 0000
    uint8_t buff[] = {0xad, 0x02};
    size_t n = 10;
    double expected = 0.527089;
    double result = fntest_monobit(buff, sizeof(buff), n);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}
// monobit 2 - from section 2.1.8
TEST_CASE("Frequency test monobit 2", tag) {
    size_t n = 100;
    int bitstr[] = {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1,
                  0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1,
                  0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0,
                  0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0};
    uint8_t buff[] = {0x93, 0xf0, 0x5b, 0x45, 0x84, 0x16, 0x43, 0x2c, 0x23, 0x63, 0x46, 0xd1, 0x01};
    // check if buff = bitstr
    for (size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL_INT(bitstr[i], GET_BIT(buff, i));
    }
    double expected = 0.109599;
    double result = fntest_monobit(buff, sizeof(buff), n);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}
