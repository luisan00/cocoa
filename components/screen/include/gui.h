#ifndef GUI_H
#define GUI_H

#include "esp_err.h"
#include "lvgl.h"

esp_err_t gui_init(lv_obj_t *scr);
esp_err_t gui_deinit(void);

#endif /* GUI_H */