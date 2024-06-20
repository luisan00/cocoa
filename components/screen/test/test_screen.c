#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_spiffs.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_dma_utils.h"
#include "lvgl.h"



#include <string.h>

#include <stdlib.h>

#include "unity.h"

#include "screen.h"
#include "logger.h"

static const char tag[] = "[screen]";

// storage_stats
TEST_CASE("mockup test case", tag) {

    TEST_ASSERT_EQUAL_INT(0, 0);
    TEST_ASSERT_EQUAL_INT(1, 1);
    TEST_ASSERT_EQUAL_INT(2, 2);
    TEST_ASSERT_EQUAL_INT(3, 3);
}
