#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "screen.h"
#include <stdio.h>

static const char *TAG = __FILE__;

void app_main(void) {
    esp_err_t res = screen_init();

    if (res != ESP_OK) {
        ESP_LOGE(TAG, "Trying to start the display, Error: %s", esp_err_to_name(res));
    }
}
