/**
 * @brief
 * @{
 */
#ifndef HMI_H
#define HMI_H

#ifdef __cplusplus
extern "C" {
#endif
#include "driver/gpio.h"
#include "helpers.h"

#define PIN_BTN_0 GPIO_NUM_0
#define PIN_BTN_1 GPIO_NUM_14

typedef struct {
    const char *name;
    int pin;
    gpio_config_t config;
} hmi_dev_t;



static hmi_dev_t hmi_dev[] = {
    {
        .name = "button 0",
        .pin = PIN_BTN_0,
        .config =
            {
                .pin_bit_mask = 1ULL << PIN_BTN_0,
                .mode = GPIO_MODE_INPUT,
                .pull_up_en = 0,
                .pull_down_en = 0,
                .intr_type = GPIO_INTR_DISABLE,
            },
    },
    {
        .name = "button 1",
        .pin = PIN_BTN_1,
        .config =
            {
                .pin_bit_mask = 1ULL << PIN_BTN_1,
                .mode = GPIO_MODE_INPUT,
                .pull_up_en = 0,
                .pull_down_en = 0,
                .intr_type = GPIO_INTR_DISABLE,
            },
    },
};

#define HMI_NUMOF   ARRAY_SIZEOF(hmi_dev)

/**
 * @brief get and return the status of the given dev
 * @param [in] dev
 * @return 1 or 0
 */
int btn_read(hmi_dev_t dev);


//

#ifdef __cplusplus
}
#endif
#endif /* HMI_H */
/** @} */
