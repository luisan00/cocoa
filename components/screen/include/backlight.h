/**
 * @brief
 * @{
 */
#ifndef BACKLIGHT_H
#define BACKLIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include "esp_err.h"

/**
 * @brief The back light can be controlled by PWM, it's done using the LEDC API.
 * @{
 */
#define LEDC_OUTPUT 38                  /*!> GPIO pin */
#define LEDC_TIMER LEDC_TIMER_0         /*!> Timer 0 will be used for this purpose */
#define LEDC_MODE LEDC_LOW_SPEED_MODE   /*!> Speed mode */
#define LEDC_CHANNEL LEDC_CHANNEL_0     /*!> Channel */
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT /*!> Set duty resolution to 13 bits */
#define LEDC_DUTY(x) ((pow(2, LEDC_DUTY_RES) - 1) * x) / 100 /*!> brightness % */
#define LEDC_FREQUENCY (5000)                                /*!> Set frequency at 5 kHz */
/** @} */

/**
 * @brief power on the backlight
 * @param [in] duty value in percentage 0 ~ 100
 * @return ESP_OK or others on error
 */
esp_err_t set_backlight_on(int duty);

/**
 * @brief change backlight brightness to [duty] percentage
 * @param [in] duty value in percentage 0 ~ 100
 * @return ESP_OK or others on error
 */
esp_err_t set_backlight_brightness(int duty);

/**
 * @brief gets brightness percentage in the range 0 ~ 100
 * @return brightness value
 */
int get_backlight_brightness(void);

/**
 * @brief power off the backlight
 * @return ESP_OK or others on error
 */
esp_err_t set_backlight_off(void);

#ifdef __cplusplus
}
#endif

#endif /* BACKLIGHT_H */
/** @} */
