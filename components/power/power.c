#include "esp_adc/adc_oneshot.h"
#include <soc/adc_channel.h>
#include "power.h"
#include "logger.h"

// ADC handle for battery voltage monitoring
static adc_oneshot_unit_handle_t adc_handle;

// ADC calibration handle for battery voltage monitoring
static adc_cali_handle_t adc_cali_handle;

esp_err_t init_battery_adc(void) {
    if (adc_handle == NULL) {
        /* Initialize ADC */
        const adc_oneshot_unit_init_cfg_t adc_cfg = {
            .unit_id = ADC_UNIT_1,
        };
        ESP_ERROR_CHECK(adc_oneshot_new_unit(&adc_cfg, &adc_handle));
    }
    return ESP_OK;
}

esp_err_t init_battery_monitor(void) {
    ESP_LOGI(__func__, "Configuring battery monitor...");
    /* Initialize ADC and get ADC handle */
    ESP_ERROR_CHECK(init_battery_adc());

    /* Init ADC channels */
    const adc_oneshot_chan_cfg_t adc_chan_cfg = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_3, &adc_chan_cfg));

    /* ESP32-S3 supports Curve Fitting calibration scheme */
    const adc_cali_curve_fitting_config_t cali_config = {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    ESP_ERROR_CHECK(adc_cali_create_scheme_curve_fitting(&cali_config, &adc_cali_handle));
    return ESP_OK;
}

int get_battery_voltage(void) {
    int voltage;
    int adc_raw;

    assert(adc_handle);

    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, ADC_CHANNEL_3, &adc_raw));
    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc_cali_handle, adc_raw, &voltage));
    return voltage * 2;
}

int usb_power_connected(void) { return -1; }