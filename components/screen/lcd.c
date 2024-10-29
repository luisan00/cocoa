#include <stdio.h>
#include <math.h>
#include "esp_log.h"
#include "esp_lcd_panel_st7789.h"
#include "driver/ledc.h"

#include "lcd.h"

static const char *TAG = "esp_idf_t_display_s3";

// initialize the LCD I80 bus
static void init_lcd_i80_bus(esp_lcd_panel_io_handle_t *io_handle, void *user_ctx) {

    ESP_LOGI(TAG, "Initializing Intel 8080 bus...");

    esp_lcd_i80_bus_handle_t i80_bus = NULL;

    esp_lcd_i80_bus_config_t bus_config = {
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .dc_gpio_num = LCD_DC,
        .wr_gpio_num = LCD_WR,
        .data_gpio_nums =
            {
                LCD_DATA0,
                LCD_DATA1,
                LCD_DATA2,
                LCD_DATA3,
                LCD_DATA4,
                LCD_DATA5,
                LCD_DATA6,
                LCD_DATA7,
            },
        .bus_width = 8,
        .max_transfer_bytes = LCD_H_RES * LCD_V_RES * sizeof(uint16_t) + 8,
        .psram_trans_align = 64,
        .sram_trans_align = 4,
    };

    ESP_ERROR_CHECK(esp_lcd_new_i80_bus(&bus_config, &i80_bus));

    esp_lcd_panel_io_i80_config_t io_config = {
        .cs_gpio_num = LCD_CS,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ,
        .trans_queue_depth = 20,
        .dc_levels =
            {
                .dc_idle_level = 0,
                .dc_cmd_level = 0,
                .dc_dummy_level = 0,
                .dc_data_level = 1,
            },
        .flags =
            {
                .swap_color_bytes = !LV_COLOR_16_SWAP, // Swap can be done in LvGL (default) or DMA
            },
        .user_ctx = user_ctx,
        .lcd_cmd_bits = LCD_CMD_BITS,
        .lcd_param_bits = LCD_PARAM_BITS,
    };

    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_config, io_handle));
}

static void init_lcd_panel(esp_lcd_panel_io_handle_t io_handle, esp_lcd_panel_handle_t *panel) {
    esp_lcd_panel_handle_t panel_handle = NULL;

    ESP_LOGI(__func__, "...");
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = LCD_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));

    esp_lcd_panel_reset(panel_handle);
    esp_lcd_panel_init(panel_handle);

    esp_lcd_panel_invert_color(panel_handle, true);

    // landscape, buttons on left, screen on right
    esp_lcd_panel_swap_xy(panel_handle, true);
    esp_lcd_panel_mirror(panel_handle, false, true);
    esp_lcd_panel_set_gap(panel_handle, 0, 35);

    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    *panel = panel_handle;
}

static void lcd_power_init(void) {
    ESP_LOGI(TAG, "Configuring LCD PWR GPIO...");
    gpio_config_t lcd_pwr_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << LCD_PWR,
    };
    ESP_ERROR_CHECK(gpio_config(&lcd_pwr_gpio_config));
    gpio_set_level(LCD_PWR, LCD_PWR_ON);

    ESP_LOGI(TAG, "Configuring LCD RD GPIO...");
    gpio_config_t lcd_rd_gpio_config = {
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pin_bit_mask = 1ULL << LCD_RD,
    };
    ESP_ERROR_CHECK(gpio_config(&lcd_rd_gpio_config));
}

esp_err_t lcd_brightness_init(void) {
    ESP_LOGI(TAG, "Configuring LCD Brightness...");
    // Setup LEDC peripheral for PWM backlight control
    const ledc_channel_config_t lcd_backlight_channel = {
        .gpio_num = LCD_BL,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = 0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = 1,
        .duty = 0,
        .hpoint = 0,
    };
    const ledc_timer_config_t lcd_backlight_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = 1,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    ESP_ERROR_CHECK(ledc_timer_config(&lcd_backlight_timer));
    ESP_ERROR_CHECK(ledc_channel_config(&lcd_backlight_channel));

    return ESP_OK;
}

esp_err_t lcd_brightness_set(int brightness_percent) {
    if (brightness_percent > 100) {
        brightness_percent = 100;
    }
    if (brightness_percent < 0) {
        brightness_percent = 0;
    }

    ESP_LOGI(TAG, "Setting LCD backlight: %d%%", brightness_percent);
    uint32_t duty_cycle =
        (1023 * brightness_percent) / 100; // LEDC resolution set to 10bits, thus: 100% = 1023
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, 0, duty_cycle));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, 0));
    return ESP_OK;
}

esp_err_t lcd_backlight_off(void) {
    ESP_ERROR_CHECK(lcd_brightness_set(0));
    return ESP_OK;
}

esp_err_t lcd_backlight_on(void) {
    ESP_ERROR_CHECK(lcd_brightness_set(100));
    return ESP_OK;
}

static lv_disp_t *lcd_lvgl_add_disp(esp_lcd_panel_io_handle_t io_handle,
                                    esp_lcd_panel_handle_t panel_handle) {
    ESP_LOGI(TAG, "Adding display driver to lvgl port...");
    /* Add LCD screen */
    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = io_handle,
        .panel_handle = panel_handle,
        .buffer_size = LVGL_BUFFER_SIZE,
        .double_buffer = true,
        .hres = LCD_H_RES,
        .vres = LCD_V_RES,
        .monochrome = false,
        /* Rotation values must be same as used in esp_lcd for initial settings of the screen */
        .rotation =
            {
                .swap_xy = true,
                .mirror_x = false,
                .mirror_y = true,
            },
        .flags = {
            .buff_spiram = true,
        }};
    return lvgl_port_add_disp(&disp_cfg);
}

esp_err_t lcd_init(lv_disp_drv_t disp_drv, lv_disp_t **disp_handle, bool backlight_on) {
    ESP_LOGI(TAG, "Initializing LVGL port...");
    /* lvgl_port initialization */
    const lvgl_port_cfg_t lvgl_cfg = {
        .task_priority = LVGL_TASK_PRIORITY,
        .task_stack = LVGL_TASK_STACK_SIZE,
        .task_affinity = 1,
        .task_max_sleep_ms = LVGL_MAX_SLEEP_MS,
        .timer_period_ms = LVGL_TICK_PERIOD_MS,

    };

    esp_err_t err = lvgl_port_init(&lvgl_cfg);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "error initializing lvgl port!");
        return err;
    }

    lcd_power_init();
    ESP_ERROR_CHECK(lcd_brightness_init());

    /* LCD IO */
    esp_lcd_panel_io_handle_t io_handle = NULL;
    init_lcd_i80_bus(&io_handle, &disp_drv);

    /* LCD driver initialization */
    esp_lcd_panel_handle_t panel_handle = NULL;
    init_lcd_panel(io_handle, &panel_handle);

    lv_disp_t *disp_hdl = lcd_lvgl_add_disp(io_handle, panel_handle);

    *disp_handle = disp_hdl;

    if (backlight_on) {
        lcd_backlight_on();
    }
    return ESP_OK;
}