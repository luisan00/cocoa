#include "unity.h"
#include "power.h"
#include "logger.h"

static const char tag[] = "[power]";

TEST_CASE("Init adc", tag) { TEST_ASSERT_EQUAL_INT(0, init_battery_adc()); }
TEST_CASE("Init battery monitor", tag) { TEST_ASSERT_EQUAL_INT(0, init_battery_monitor()); }
TEST_CASE("Read voltage in mV", tag) {

    int mV = get_battery_voltage();
    logi("Battery: %d mV", mV);
    TEST_ASSERT_GREATER_THAN_INT(0, mV);
}