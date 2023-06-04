#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

#include "lvgl.h"
#include "lv_qrcode.h"

#include "screen.h"
#include "screen_config.h"
#include "gui.h"
#include "logger.h"

void gui_init(lv_obj_t *scr) {
    lv_coord_t qr_size = 0;
    lv_obj_t *qr = lv_qrcode_create(scr, 0, lv_color_black(), lv_color_white());
}

void gui_deinit(void) {}
