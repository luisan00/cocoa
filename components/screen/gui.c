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
    lv_color_t bg_color = lv_color_white();
    lv_color_t fg_color = lv_color_black();
    lv_obj_t *qr = lv_qrcode_create();
    lv_qrcode_update(qr, "hola", 5);

}

void gui_deinit(void) {}
