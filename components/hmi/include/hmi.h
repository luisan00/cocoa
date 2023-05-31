/**
 * @brief
 * @{
 */
#ifndef HMI_H
#define HMI_H

#include "esp_err.h"
#include "driver/gpio.h"
#include "helpers.h"

#ifdef __cplusplus
extern "C" {
#endif


#define PIN_BTN_0 GPIO_NUM_0
#define PIN_BTN_1 GPIO_NUM_14
#define HMI_INTR_FLAG_DEFAULT 0

/**
 * @{
 */
typedef struct {
    const char *name;
    int pin;
    const gpio_config_t config;
} hmi_dev_t;
/** @} */

/**
 * @{
 */
static hmi_dev_t hmi_dev[] = {
    {
        .name = "button 0",
        .pin = PIN_BTN_0,
        .config =
            {
                .pin_bit_mask = 1ULL << PIN_BTN_0,
                .mode = GPIO_MODE_INPUT,
                .pull_up_en = GPIO_PULLUP_ENABLE,
                .pull_down_en = GPIO_PULLDOWN_DISABLE,
                .intr_type = GPIO_INTR_ANYEDGE,
            },
    },
    {
        .name = "button 1",
        .pin = PIN_BTN_1,
        .config =
            {
                .pin_bit_mask = 1ULL << PIN_BTN_1,
                .mode = GPIO_MODE_INPUT,
                .pull_up_en = GPIO_PULLUP_ENABLE,
                .pull_down_en = GPIO_PULLDOWN_DISABLE,
                .intr_type = GPIO_INTR_ANYEDGE,
            },
    },
};
/** @} */
#define HMI_NUMOF ARRAY_SIZEOF(hmi_dev)

esp_err_t hmi_start(void *handler);

/**
 * @brief get and return the status of the given dev, only for unit-testing purposes
 * @param [in] dev
 * @return 1 or 0
 */
int btn_read(hmi_dev_t dev);

#ifdef __cplusplus
}
#endif
#endif /* HMI_H */
/** @} */
