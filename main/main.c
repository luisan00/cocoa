#include <stdio.h>
//
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

static const char *TAG = __FILE__;
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
    esp_err_t res;

    // POWER
    //  - ToDo
    // STORAGE
    //  - ToDo
    // SCREEN

    

    res = screen_init();
    if (res != ESP_OK) {
        loge("Starting screen: %s", esp_err_to_name(res));
        // report malfunction
    }
    // screen ready
    //
    // [h]uman to [m]achine [i]nterface
    res = hmi_start();
    if (res != ESP_OK) {
        loge("Starting hmi: %s", esp_err_to_name(res));
    }
    // hmi ready
    //
    // storage

    // check if the device is already initialized
    // something like check_if_init();
    // if true then do something
    // if false then do something else
}