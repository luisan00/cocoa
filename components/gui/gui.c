#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/ringbuf.h"

#include "helpers.h"
#include "logger.h"

#include "lvgl.h"

#include "gui.h"
#include "gui_events.h"
#include "lv_theme_custom.h"

RingbufHandle_t gui_ringbuf;

void show_mnemonic(lv_obj_t *scr, const char **mnemonic, size_t mnemonic_size) {
    // show only mnemonic
    lv_obj_t *_label[mnemonic_size];
    int x_spacing = 100;
    int y_spacing = 20;

    int x_offset = 0;
    int y_offset = 0;

    for (size_t i = 0; i < mnemonic_size; i++) {

        _label[i] = lv_label_create(scr);

        char mn_index[14];
        snprintf(mn_index, sizeof(mn_index), "%2d%1s%-8s", i + 1, ". ", mnemonic[i]);

        lv_label_set_text(_label[i], mn_index);
        // 1st column col 0
        if (i >= 0 && i < 8) {
            x_offset = 0;
            y_offset = y_spacing * i - 0;
        } else if (i >= 8 && i < 16) {
            x_offset = x_spacing;
            y_offset = y_spacing * i - (y_spacing * 8);
        } else if (i >= 16) {
            x_offset = x_spacing * 2;
            y_offset = y_spacing * i - (y_spacing * 16);
        }

        lv_obj_align(_label[i], LV_ALIGN_TOP_LEFT, x_offset, y_offset);
    }
}
void gui_init(lv_obj_t *screen) {
    custom_theme_init();
}

void gui_task(void *args) {
    // ToDo
}
