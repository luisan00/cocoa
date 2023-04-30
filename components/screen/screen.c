/**
 * Copyright (c) 2023 luisan00 <luisan00@hotmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#include <esp_timer.h>
#include "esp_err.h"
#include "esp_log.h"


#include "lv_conf.h"
#include "lvgl.h"

#include "screen.h"
#include "screen_config.h"

esp_lcd_panel_io_handle_t io_handle = NULL;
static lv_disp_drv_t screen_drv;
static lv_disp_draw_buf_t screen_buf;
static lv_color_t *lv_screen_buf;

static bool is_init_lvgl = false;

static bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    if (is_init_lvgl)
    {
        lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
        lv_disp_flush_ready(disp_driver);
    }
    return false;
}
static void scr_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // copy a buffer's content to a specific area of the display

    //esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
}

esp_err_t screen_init()
{
    esp_err_t res;

    gpio_config_t pwr_cfg = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << SCR_POWER_ON,
    };

    res = gpio_config(&pwr_cfg);

    if (res != ESP_OK)
    {
        ESP_LOGE("ERROR", "Configuring power GPIO: %s", esp_err_to_name(res));
    }

    res = gpio_set_level(SCR_POWER_ON, 1);

    if (res != ESP_OK)
    {
        ESP_LOGE("ERROR", "Setting power on the screen: %s", esp_err_to_name(res));
    }

    esp_lcd_i80_bus_handle_t i80_bus = NULL;

    esp_lcd_i80_bus_config_t bus_config = {
        .dc_gpio_num = SCR_DC,
        .wr_gpio_num = SCR_WR,
        .clk_src = LCD_CLK_SRC_PLL160M,
        .data_gpio_nums =
            {
                SCR_D0,
                SCR_D1,
                SCR_D2,
                SCR_D3,
                SCR_D4,
                SCR_D5,
                SCR_D6,
                SCR_D7,
            },
        .bus_width = 8,
        .max_transfer_bytes = LVGL_LCD_BUF_SIZE * sizeof(uint16_t),
    };

    res = esp_lcd_new_i80_bus(&bus_config, &i80_bus);

    if (res != ESP_OK)
    {
        ESP_LOGE("ERROR", "function 'esp_lcd_new_i80_bus' return non ok status: %s", esp_err_to_name(res));
    }
    esp_lcd_panel_io_i80_config_t io_config = {
        .cs_gpio_num = SCR_CS,
        .pclk_hz = EXAMPLE_LCD_PIXEL_CLOCK_HZ,
        .trans_queue_depth = 20,
        .on_color_trans_done = example_notify_lvgl_flush_ready,
        .user_ctx = &screen_drv,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .dc_levels = {
            .dc_idle_level = 0,
            .dc_cmd_level = 0,
            .dc_dummy_level = 0,
            .dc_data_level = 1,
        },
    };

    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle));

    esp_lcd_panel_handle_t panel_handle = NULL;

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = SCR_RST,
        .color_space = ESP_LCD_COLOR_SPACE_RGB,
        .bits_per_pixel = 16,
    };
    esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle);
    esp_lcd_panel_reset(panel_handle);
    esp_lcd_panel_init(panel_handle);
    esp_lcd_panel_invert_color(panel_handle, true);

    esp_lcd_panel_swap_xy(panel_handle, true);
    esp_lcd_panel_mirror(panel_handle, false, true);
    // the gap is LCD panel specific, even panels with the same driver IC, can
    // have different gap value
    esp_lcd_panel_set_gap(panel_handle, 0, 35);

    /* Lighten the screen with gradient */
    ledc_timer_config_t ledc_bl_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY, // Set output frequency at 5 kHz
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_bl_timer));
    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = SCR_BL,
        .duty = 0, // Set duty to 0%
        .hpoint = 0,
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    for (int percent = 0; percent < 326; percent++)
    {
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY(percent)));
        // Update duty to apply the new value
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }

    lv_init();
    lv_screen_buf = (lv_color_t *)heap_caps_malloc(LVGL_LCD_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
    /*Initialize the display*/
    lv_disp_drv_init(&screen_drv);
    /*Change the following line to your display resolution*/
    screen_drv.hor_res = SCR_H_RES;
    screen_drv.ver_res = SCR_V_RES;
    screen_drv.flush_cb = scr_lvgl_flush_cb;
    screen_drv.draw_buf = &screen_buf;
    screen_drv.user_data = panel_handle;
    lv_disp_drv_register(&screen_drv);

    is_init_lvgl = true;

    
    return ESP_OK;
}