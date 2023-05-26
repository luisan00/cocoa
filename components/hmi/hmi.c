#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "hmi.h"

int btn_read(hmi_dev_t dev) {
    return gpio_get_level(dev.pin);

};