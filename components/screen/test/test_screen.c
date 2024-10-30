#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "lcd.h"
#include "lv_demos.h"
static const char tag[] = "[screen]";

// LVGL display driver
static lv_disp_drv_t disp_drv;
// LVGL display handle
static lv_disp_t *disp_handle;

TEST_CASE("Init the lcd panel", tag) {
    //
    TEST_ASSERT_EQUAL_INT(0, lcd_init(disp_drv, &disp_handle, false));
};

TEST_CASE("Set BL to 50 percent ", tag) {
    //
    TEST_ASSERT_EQUAL_INT(0, lcd_brightness_set(50));
};

#if defined(LV_USE_DEMO_WIDGETS) && LV_USE_DEMO_WIDGETS
TEST_CASE("Run LVGL demo widgets ", tag) {
    //
    lv_demo_widgets();
    return TEST_PASS;
};
#endif

#if defined(LV_USE_DEMO_MUSIC) && LV_USE_DEMO_MUSIC
TEST_CASE("Run LVGL demo music ", tag) {
    //
    lv_demo_music();
};
#endif
