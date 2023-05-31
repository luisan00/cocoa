#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/ringbuf.h"

#include "hmi.h"

esp_err_t hmi_start(void *handler) {

    for (size_t i = 0; i < HMI_NUMOF; i++) {
        gpio_config(&hmi_dev[i].config);
    }
    // Install gpio isr service
    gpio_install_isr_service(0);

    for (size_t i = 0; i < HMI_NUMOF; i++) {
        gpio_isr_handler_add(hmi_dev[i].pin, handler, (void*)hmi_dev[i].pin);
    }
    //
    return ESP_OK;
}

int btn_read(hmi_dev_t dev) { return gpio_get_level(dev.pin); };
