
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_err.h"

#include "esp_task_wdt.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "screen.h"

void runMonitor(void *name)
{
    uint64_t start = esp_timer_get_time();

    while (1)
    {

        uint64_t elapsed = esp_timer_get_time() - start;

        ESP_LOGD(__func__, "%llu seconds", elapsed / 1000000);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{

    esp_err_t res = screen_init();

    if (res != ESP_OK)
    {
        ESP_LOGE("ERROR", "starting screen : %s", esp_err_to_name(res));
    }
    // Start monitor task
    xTaskCreate(runMonitor, "Monitor", 5000, NULL, 4, NULL);
}