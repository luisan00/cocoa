#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "lcd.h"

static const char tag[] = "[screen]";

TEST_CASE("Init the lcd panel", tag) {
    // LVGL display driver
    static lv_disp_drv_t disp_drv;
    // LVGL display handle
    static lv_disp_t *disp_handle;
    TEST_ASSERT_EQUAL_INT(0, lcd_init(disp_drv, &disp_handle, true));
}
