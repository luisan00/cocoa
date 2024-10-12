#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"

#include "lcd.h"
#include "screen.h"
#include "logger.h"

static const char tag[] = "[screen]";

// init panel
TEST_CASE("Init the lcd panel", tag) {
    //
    TEST_ASSERT_EQUAL_INT(init_i80_bus(), 0);
}

// lvgl version
TEST_CASE("Get LVGL version", tag) {
    // Current LVGL version is defined by `LVGL_VERSION_MAJOR`, `LVGL_VERSION_MINOR` and
    // `LVGL_VERSION_PATH`
    logd("\x1b[48:5:31m%s:%d.%d.%d\x1b[0m\n", "LVGL version: ", LVGL_VERSION_MAJOR,
         LVGL_VERSION_MINOR, LVGL_VERSION_PATCH);
    TEST_ASSERT(LVGL_VERSION_MAJOR >= 0);
    TEST_ASSERT(LVGL_VERSION_MINOR >= 0);
    TEST_ASSERT(LVGL_VERSION_PATCH >= 0);
}

//