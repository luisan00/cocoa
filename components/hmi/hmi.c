#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

//
#include "logger.h"
#include "hmi.h"

static QueueHandle_t hmi_evt_queue = NULL;
static void IRAM_ATTR hmi_isr_handler(void *arg);
static void hmi_task(void *arg);

esp_err_t hmi_start(void) {
    esp_err_t res;
    for (size_t i = 0; i < HMI_NUMOF; i++) {
        res = gpio_config(&hmi_dev[i].config);
        if (res != ESP_OK) {
            // report malfunction
            loge("hmi_start(): %s", esp_err_to_name(res));
            return res;
        } else {
            // print log
            logd("hmi_start(): %s", esp_err_to_name(res));
        }
    }
    // Queue to handle hmi events from isr
    hmi_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    // Start gpio task
    xTaskCreate(hmi_task, "hmi_task", 2048, NULL, 10, NULL);

    // Install gpio isr service
    res = gpio_install_isr_service(ESP_INTR_FLAG_IRAM);
    if (res != ESP_OK) {
        loge("install isr: %s", esp_err_to_name(res));
        return res;
    }
    logd("install isr service: %s", esp_err_to_name(res));
    
    // 
    for (size_t i = 0; i < HMI_NUMOF; i++) {
        res = gpio_isr_handler_add(hmi_dev[i].pin, hmi_isr_handler, (void *)hmi_dev[i].pin);
        if (res != ESP_OK) {
            loge("isr handler add: %s", esp_err_to_name(res));
            return res;
        } else {
            logd("isr handler for %s: %s", hmi_dev[i].name, esp_err_to_name(res));
        }
    }
    //
    return ESP_OK;
}

static void IRAM_ATTR hmi_isr_handler(void *arg) {
    uint32_t gpio_num = (uint32_t)arg;
    xQueueSendFromISR(hmi_evt_queue, &gpio_num, NULL);
}

static void hmi_task(void *arg) {
    uint32_t io_num;
    for (;;) {
        if (xQueueReceive(hmi_evt_queue, &io_num, portMAX_DELAY)) {
            printf("GPIO[%" PRIu32 "] intr, val: %d\n", io_num, gpio_get_level(io_num));
        }
    }
}
int btn_read(hmi_dev_t dev) { return gpio_get_level(dev.pin); };
