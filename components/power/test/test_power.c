#include "unity.h"
#include "power.h"
#include "logger.h"


static const char tag[] = "[power]";

TEST_CASE("read voltage", tag) {
    int mV = get_batt_voltage();
    logi("battery %d mV", mV);
}