#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "lvgl.h"

#include "unity.h"

#include "screen.h"
#include "logger.h"

static const char tag[] = "[screen]";

// storage_stats
TEST_CASE("Get LVGL version", tag) {
    // Current LVGL version is defined by LVGL_VERSION_[int] Where int can be; MAJOR, MINOR or PATH
    int major = LVGL_VERSION_MAJOR; // 9
    int minor = LVGL_VERSION_MINOR; // 1
    int path = LVGL_VERSION_PATCH;  // 0

    logd("Current version : %d.%d.%d", major, minor, path);

    TEST_ASSERT(LVGL_VERSION_MAJOR >= 0);
    TEST_ASSERT(LVGL_VERSION_MINOR >= 0);
    TEST_ASSERT(LVGL_VERSION_PATCH >= 0);
}
