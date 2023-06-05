#ifndef GUI_H
#define GUI_H
#include "lvgl.h"
#include "screen_config.h"

#define GL_LCD_BUF_SIZE (SCREEN_H_RES * SCREEN_V_RES)
#define SCREEN_LVGL_TICK_PERIOD_MS 2

void gl_init(void);

void gui_init(lv_obj_t *screen);
void gui_deinit(void);

#endif /* GUI_H */