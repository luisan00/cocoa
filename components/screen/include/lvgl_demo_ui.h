#ifndef MAIN_LVGL_DEMO_UI_H_
#define MAIN_LVGL_DEMO_UI_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <math.h>
#include "lvgl.h"
#include "esp_log.h"

/* MACROS --------------------------------------------------------------------*/
#ifndef PI
#define PI  (3.14159f)
#endif

LV_IMG_DECLARE(esp_logo)

//LV_IMG_DECLARE(ue_text)

LV_IMG_DECLARE(esp_text)

/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef struct
{
    lv_obj_t *scr;
    int count_val;
} my_timer_context_t;
/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void lvgl_demo_ui(lv_obj_t *scr);


#endif /* MAIN_LVGL_DEMO_UI_H_ */