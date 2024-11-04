#include "unity.h"
#include "power.h"
#include "logger.h"

static const char tag[] = "[power]";

TEST_CASE("Init Power (ADC read only!)", tag) { TEST_ASSERT_EQUAL_INT(0, power_init()); }
TEST_CASE("Read battery voltage", tag) {
    uint16_t mV = power_get_vbat();
    logi("Battery: %d mV", mV);
    TEST_ASSERT_GREATER_THAN_INT(0, mV);
}