#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

#include "lvgl.h"
#include "screen.h"
#include "screen_config.h"
#include "gui.h"

// ToDo
//
// __Initial section__
//
// 1. show splash sreen
// 2. if:
//      2.1. dev. initialized: should go to [It is]
//      2.2. dev. is not initialized: go to [It is not]
//
// __It is not__
//
// 1. Set pin
// 2. Seed -> bip 39/32, 24 + 1
// 3. Verification.
// 4. Reset, on next boot should return to Initial section. 
//
// __It is__
// 
// 1. PIN input
// 2. 

esp_err_t gui_init(lv_obj_t *scr) {
    // set background color to full black
    lv_obj_set_style_bg_color(scr, lv_color_hex(COLOR_BLACK), LV_PART_MAIN);

    return ESP_OK;
}

esp_err_t gui_deinit(void) {
    lv_deinit();
    return ESP_OK;
}
