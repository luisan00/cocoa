#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "logger.h"
#include "hmi.h"

static QueueHandle_t gpio_evt_queue = NULL;
static void hmi_isr_handler(void *arg);
static void hmi_task(void *arg);

esp_err_t hmi_start(void *arg) {

    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    xTaskCreate(hmi_task, "hmi_task", 2048, NULL, 10, NULL);

    for (size_t i = 0; i < HMI_NUMOF; i++) {
        gpio_config(&hmi_dev[i].config);
    }
    // Install gpio isr service
    gpio_install_isr_service(0);

    for (size_t i = 0; i < HMI_NUMOF; i++) {
        gpio_isr_handler_add(hmi_dev[i].pin, hmi_isr_handler, (void *)hmi_dev[i].pin);
    }
    //
    return ESP_OK;
}

static void hmi_isr_handler(void *arg) {
    uint32_t pin = (uint32_t)arg;
    xQueueSendFromISR(gpio_evt_queue, &pin, NULL);
}

static void hmi_task(void *arg) {
    uint32_t io_num;
    for (;;) {
        if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY) && gpio_get_level(io_num) == 0) {
            printf("GPIO[%" PRIu32 "] intr, val: %d\n", io_num, gpio_get_level(io_num));
        }
    }
}

int btn_read(hmi_dev_t dev) { return gpio_get_level(dev.pin); };
