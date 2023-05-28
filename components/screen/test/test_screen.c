#include "esp_log.h"
#include "unity.h"

static const char tag[] = "[screen]";

// backlight:
//   - power on
//   - set brightness
//   - power off
// driver
//   - i80 bus
//   - i80 panel
//   - lcd panel (ST7789)
// little visual graphics library
//   - ?

TEST_CASE("screen", tag)
{
    TEST_ASSERT_EQUAL(1, 1);
}