#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

#include "lvgl.h"
#include "lv_conf.h"
#include "screen.h"
#include "screen_config.h"
#include "gui.h"
#include "logger.h"

static lv_style_t style;
static lv_style_t bgStyle;
static lv_style_t titleStyle;

static lv_obj_t *dis;
static lv_obj_t *meter;

static lv_obj_t *lebel;
static lv_obj_t *title;

lv_obj_t *tv1;
lv_obj_t *tv2;
lv_obj_t *tv3;

static lv_color_t arc_color[] = {
    LV_COLOR_MAKE(0xFF, 0x00, 0x28),
    LV_COLOR_MAKE(0x14, 0xFF, 0x00),
    LV_COLOR_MAKE(0xFF, 0xFF, 0xFF),
};
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

void lvgl_demo_ui(lv_obj_t *scr);

void set_value(void *indic, int32_t v) {
    lv_meter_set_indicator_end_value(meter, indic, v);
}

void gui_init(lv_obj_t *scr) {

    /* page 2 */
    lv_obj_t * meter = lv_meter_create(scr);
    lv_obj_center(meter);
    lv_obj_set_size(meter, 170, 170);

    /*Remove the circle from the middle*/
    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);

    /*Add a scale first*/
    lv_meter_scale_t *scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 11, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 1, 2, 15, lv_color_hex3(0xeee), 10);
    lv_meter_set_scale_range(meter, scale, 0, 100, 270, 90);

    /*Add a three arc indicator*/
    lv_meter_indicator_t *indic1 = lv_meter_add_arc(meter, scale, 10, lv_color_hex3(0x00F), 0);
    lv_meter_indicator_t *indic2 = lv_meter_add_arc(meter, scale, 10, lv_color_hex3(0x0F0), -10);
    lv_meter_indicator_t *indic3 = lv_meter_add_arc(meter, scale, 10, lv_color_hex3(0xF00), -20);

    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_set_repeat_delay(&a, 100);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);

    lv_anim_set_time(&a, 2000);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_var(&a, indic1);
    lv_anim_start(&a);

    lv_anim_set_time(&a, 1000);
    lv_anim_set_playback_time(&a, 1000);
    lv_anim_set_var(&a, indic2);
    lv_anim_start(&a);

    lv_anim_set_time(&a, 1000);
    lv_anim_set_playback_time(&a, 2000);
    lv_anim_set_var(&a, indic3);
    lv_anim_start(&a);

}

void gui_deinit(void) {}
