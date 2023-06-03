#include <stdio.h>
#include "driver/ledc.h"
#include "logger.h"
#include "backlight.h"

esp_err_t set_backlight_on(int duty) {
    if (duty > 100) {
        duty = 100;
    }
    if (duty < 0) {
        duty = 0;
    }
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    esp_err_t res = ledc_timer_config(&ledc_timer);
    if (res != ESP_OK) {
        loge("backlight timer cfg: %s", esp_err_to_name(res));
        return res;
    }
    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT,
        .duty = LEDC_DUTY(duty),
        .hpoint = 0,
    };
    res = ledc_channel_config(&ledc_channel);
    if (res != ESP_OK) {
        loge("backlight channel cfg: %s", esp_err_to_name(res));
        return res;
    }
    logi("backlight on: %s", esp_err_to_name(res));
    return res;
}

esp_err_t set_backlight_brightness(int duty) {
    if (duty > 100) {
        duty = 100;
    }
    if (duty < 0) {
        duty = 0;
    }
    if (duty == get_backlight_brightness()) {
        logi("new value %d is equal to old value", duty);
        return ESP_OK;
    }
    // set new value
    esp_err_t res = ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY(duty));
    if (res != ESP_OK) {
        loge("backlight duty cfg: %s", esp_err_to_name(res));
        return res;
    }
    // Update to apply the new value
    res = ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    if (res != ESP_OK) {
        loge("backlight update brightness: %s", esp_err_to_name(res));
        return res;
    }
    logi("backlight update level: %s", esp_err_to_name(res));
    return res;
}

int get_backlight_brightness(void) {
    int duty = (int)(ledc_get_duty(LEDC_MODE, LEDC_CHANNEL) * 100 / (pow(2, LEDC_DUTY_RES) - 1));
    return duty;
}

// esp_err_t ledc_stop(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t idle_level)
esp_err_t set_backlight_off(void) {
    esp_err_t res = ledc_stop(LEDC_MODE, LEDC_CHANNEL, 0);
    if (res != ESP_OK) {
        loge("backlight stop: %s", esp_err_to_name(res));
    }
    logi("backlight stop: %s", esp_err_to_name(res));
    return res;
}