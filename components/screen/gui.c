#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

#include "lvgl.h"

#include "screen.h"
#include "screen_config.h"
#include "gui.h"
#include "logger.h"

/**
 * Create a QR Code
 */
lv_obj_t *qrcode_create(const char *data, size_t data_len) {
    lv_color_t bg_color = lv_color_white();
    lv_color_t fg_color = lv_color_black();
    lv_obj_t *qr = lv_qrcode_create(lv_scr_act(), 170, fg_color, bg_color);

    lv_qrcode_update(qr, data, data_len);
    lv_obj_center(qr);

    lv_obj_set_style_border_color(qr, bg_color, 0);
    lv_obj_set_style_border_width(qr, 5, 0);
    return qr;
}

void gui_init(lv_obj_t *scr) {
    const char data[] =
        "lorem ipsum dolor sit amet consectetur adipiscing elit sed finibus ultrices arcu aliquet "
        "imperdiet lacus condimentum eget mauris congue quam eu leo condimentum gravida";
    lv_obj_t *qr = qrcode_create(data, strlen(data));
    // lv_qrcode_delete(qr);

}

void gui_deinit(void) {}
