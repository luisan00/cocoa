#include <stdio.h>
//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/ringbuf.h"
#include "esp_err.h"
#include "esp_log.h"
//
#include "bip39.h"
#include "bip32.h"
#include "rand.h"
//
#include "logger.h"
#include "power.h"
#include "screen.h"
#include "hmi.h"
#include "storage.h"

static void btn_handle(void *args);
//
// system on power:
//
// nvs on
// USB to host on and ready
// Seed on
// HMI on
// screen on
//
void app_main(void) {
    // power
    // power_ctr_init();
    // screen
    screen_init();
    // [h]uman to [m]achine [i]nterface
    hmi_start(btn_handle);
    // dashboard
    // dashboard_start();
}

static void btn_handle(void *arg) { 
    //
    uint32_t io_num = (uint32_t)arg;
    logi("aqui: %lu", io_num);
}
