#include "esp_adc/adc_oneshot.h"
#include "power.h"
#include "logger.h"

// On ESP32-S3 ADC1, CHANNEL3 is for GPIO4
#define BATTERY_ADC_CHANNEL ADC_CHANNEL_3

// ADC handle for battery voltage monitoring
static adc_oneshot_unit_handle_t adc1_handle = NULL;

// ToDo: 
// - ADC calibration before read values
// - use one shot /w cali routines 
esp_err_t power_init(void) {
    // Initialise the ADC to measure battery level
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));
    assert(adc1_handle);
    // ADC Config
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, BATTERY_ADC_CHANNEL, &config));

    return ESP_OK;
}

int power_get_vbat(void)
{
    assert(adc1_handle);
    int vbat = 0;
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, BATTERY_ADC_CHANNEL, &vbat));
    return vbat * 2;
}