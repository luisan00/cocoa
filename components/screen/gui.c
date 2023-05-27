#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

#include "lvgl.h"
#include "screen.h"
#include "screen_config.h"
#include "gui.h"

static lv_obj_t *meter;

static void spinner(void);
static void show_meter(void);
static void change_meter_value(void *indic, int32_t v);

esp_err_t gui_init(lv_obj_t *scr)
{

    lv_obj_set_style_bg_color(scr, lv_color_hex(COLOR_BLACK), LV_PART_MAIN);

    // spinner();
    // vTaskDelay(100000 / portTICK_PERIOD_MS);
    show_meter();

    return ESP_OK;
}

esp_err_t gui_deinit(void)
{
    lv_deinit();
    return ESP_OK;
}

static void spinner(void)
{
    lv_obj_t *spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
    lv_obj_set_size(spinner, SCREEN_V_RES - 5, SCREEN_V_RES - 5);
    lv_obj_center(spinner);
}

static void show_meter(void)
{

    meter = lv_meter_create(lv_scr_act());
    lv_obj_center(meter);
    lv_obj_set_size(meter, SCREEN_V_RES, SCREEN_V_RES);

    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);

    /*Add a scale first*/
    lv_meter_scale_t *scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 11, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 1, 2, 15, lv_color_hex(COLOR_BLACK), 10);
    lv_meter_set_scale_range(meter, scale, 0, 100, 270, 90);

    lv_meter_indicator_t *indic;

    /*Add a blue arc to the start*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 20);

    /*Add a red arc to the end*/
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_GREEN), 0);
    lv_meter_set_indicator_start_value(meter, indic, 80);
    lv_meter_set_indicator_end_value(meter, indic, 100);

    /*Add a needle line indicator*/
    indic = lv_meter_add_needle_line(meter,scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);

    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, change_meter_value);
    
    lv_anim_set_var(&a, indic);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_set_time(&a, 2000);
    lv_anim_set_repeat_delay(&a, 100);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}

static void change_meter_value(void *indic, int32_t v)
{
    lv_meter_set_indicator_value(meter, indic, v);
}
