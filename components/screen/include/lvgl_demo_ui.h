#ifndef MAIN_LVGL_DEMO_UI_H_
#define MAIN_LVGL_DEMO_UI_H_

#include <math.h>
#include "lvgl.h"

#ifndef PI
#define PI  (3.14159f)
#endif

LV_IMG_DECLARE(esp_logo)

LV_IMG_DECLARE(esp_text)

typedef struct
{
    lv_obj_t *scr;
    int count_val;
} my_timer_context_t;


void lvgl_demo_ui(lv_obj_t *scr);


#endif /* MAIN_LVGL_DEMO_UI_H_ */