
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  main1.c
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Aug 20, 2022
 * @brief   		:
 *
 ******************************************************************************/

/* INCLUDES ------------------------------------------------------------------*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_err.h"

#include "lvgl.h"
#include "logger.h"
#include "screen_config.h"
// #include "backlight.h"
#include "gui.h"

static void lvgl_increase_tick(void *arg);
static bool lvgl_notify_flush_ready(esp_lcd_panel_io_handle_t panel_io,
                                    esp_lcd_panel_io_event_data_t *edata, void *user_ctx);
static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map);
static void create_lv_timer_task(void);
static void lv_timer_task(void *param);

static bool lvgl_notify_flush_ready(esp_lcd_panel_io_handle_t panel_io,
                                    esp_lcd_panel_io_event_data_t *edata, void *user_ctx) {
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}

static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map) {
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // copy a buffer's content to a specific area of the display
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1,
                              color_map);
}

static void lvgl_increase_tick(void *arg) {
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(SCREEN_LVGL_TICK_PERIOD_MS);
}

static void lv_timer_task(void *param) {
    while (1) {
        // The task running lv_timer_handler should have lower priority than that running
        // `lv_tick_inc`
        lv_timer_handler();

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

static void create_lv_timer_task(void) {

    xTaskCreatePinnedToCore(lv_timer_task, "lvgl Timer", 10000, NULL, 4, NULL, 1);
}

esp_err_t screen_init(void) {
    esp_err_t res;
    static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
    static lv_disp_drv_t disp_drv;      // contains callback functions

    gpio_config_t bk_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << SCREEN_BKL,
    };

    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));
    
    esp_rom_gpio_pad_select_gpio(SCREEN_BKL);

    // esp_rom_gpio_pad_select_gpio(SCREEN_RD);
    esp_rom_gpio_pad_select_gpio(SCREEN_PWR);

    //gpio_set_direction(SCREEN_RD, GPIO_MODE_INPUT);
    gpio_set_direction(SCREEN_PWR, GPIO_MODE_OUTPUT);

    // gpio_set_level(SCREEN_RD, 1);
    gpio_set_level(SCREEN_BKL, 0);

    esp_lcd_i80_bus_handle_t i80_bus = NULL;
    esp_lcd_i80_bus_config_t bus_config = {
        .dc_gpio_num = SCREEN_DC,
        .wr_gpio_num = SCREEN_WR,
        .clk_src = LCD_CLK_SRC_PLL160M,
        .data_gpio_nums =
            {
                SCREEN_DATA0,
                SCREEN_DATA1,
                SCREEN_DATA2,
                SCREEN_DATA3,
                SCREEN_DATA4,
                SCREEN_DATA5,
                SCREEN_DATA6,
                SCREEN_DATA7,
            },
        .bus_width = 8,
        .max_transfer_bytes = LVGL_LCD_BUF_SIZE * sizeof(uint16_t),
    };
    //
    res = esp_lcd_new_i80_bus(&bus_config, &i80_bus);
    if (res != ESP_OK) {
        loge("lcd_i80_bus: %s", esp_err_to_name(res));
        return res;
    }
    logd("lcd_i80_bus: %s", esp_err_to_name(res));

    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_i80_config_t io_config = {
        .cs_gpio_num = SCREEN_CS,
        .pclk_hz = SCREEN_PX_CLOCK_HZ,
        .trans_queue_depth = 20,
        .dc_levels =
            {
                .dc_idle_level = 0,
                .dc_cmd_level = 0,
                .dc_dummy_level = 0,
                .dc_data_level = 1,
            },
        .on_color_trans_done = lvgl_notify_flush_ready,
        .user_ctx = &disp_drv,
        .lcd_cmd_bits = SCREEN_CMD_BITS,
        .lcd_param_bits = SCREEN_PARAM_BITS,
    };
    //
    res = esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle);
    if (res != ESP_OK) {
        loge("lcd_panel_io: %s", esp_err_to_name(res));
        return res;
    }
    logd("lcd_panel_io: %s", esp_err_to_name(res));

    esp_lcd_panel_handle_t panel_handle = NULL;

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = SCREEN_RST,
        .color_space = ESP_LCD_COLOR_SPACE_RGB,
        .bits_per_pixel = 16,
    };
    //
    res = esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle);
    if (res != ESP_OK) {
        loge("ST7789 driver: %s", esp_err_to_name(res));
        return res;
    }
    logd("ST7789 driver: %s", esp_err_to_name(res));
    //
    esp_lcd_panel_reset(panel_handle);
    esp_lcd_panel_init(panel_handle);
    esp_lcd_panel_invert_color(panel_handle, true);

    esp_lcd_panel_swap_xy(panel_handle, true);
    esp_lcd_panel_mirror(panel_handle, false, true);

    // the gap is LCD panel specific, even panels with the same driver IC, can have different gap
    // value
    esp_lcd_panel_set_gap(panel_handle, 0, 35);
    
    const gpio_config_t input_conf = {
        .pin_bit_mask = 1ULL << SCREEN_RD,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    gpio_config(&input_conf);

    res = gpio_set_level(SCREEN_PWR, SCREEN_PWR_ON);
    gpio_set_level(SCREEN_BKL, 1);

    if (res != ESP_OK) {
        loge("power on: %s", esp_err_to_name(res));
        return res;
    }
    logd("power on: %s", esp_err_to_name(res));

    // set_backlight_on(75);

    logd("Initializing lvgl library");
    lv_init();

    // alloc draw buffers used by LVGL
    // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
    lv_color_t *buf1 = heap_caps_malloc(LVGL_LCD_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1);

    // initialize LVGL draw buffers
    lv_disp_draw_buf_init(&disp_buf, buf1, NULL, LVGL_LCD_BUF_SIZE);

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_H_RES;
    disp_drv.ver_res = SCREEN_V_RES;
    disp_drv.flush_cb = lvgl_flush_cb;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.user_data = panel_handle;
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

    // -- end of configuration --

    // Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &lvgl_increase_tick,
        .name = "lvgl_tick",
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, SCREEN_LVGL_TICK_PERIOD_MS * 1000));
    //
    logd("UI init");
    lv_obj_t *scr = lv_disp_get_scr_act(disp);

    gui_init(scr);
    create_lv_timer_task();
    return ESP_OK;
}
