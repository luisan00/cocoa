#ifndef BACKLIGHT_H
#define BACKLIGHT_H
#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>
#include "esp_err.h"

/**
 * @brief The back light can be controlled by PWM, it's done using the LEDC API.
 * 4095 =  50%
 * 8190 = 100%
 * @{
 */

#define LEDC_OUTPUT 38
#define LEDC_TIMER LEDC_TIMER_0         /*!> Timer 0 will be used for this purpose */
#define LEDC_MODE LEDC_LOW_SPEED_MODE   /*!> Speed mode */
#define LEDC_CHANNEL LEDC_CHANNEL_0     /*!> Channel */
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT /*!> Set duty resolution to 13 bits */
#define LEDC_DUTY(x) ((pow(2, LEDC_DUTY_RES) - 1) * x) / 100 /*!> brightness % */
#define LEDC_FREQUENCY (5000) // Frequency in Hertz. Set frequency at 5 kHz
/** @} */

/**
 * @brief power on the backlight
 */
esp_err_t set_backlight_on(int duty);

/**
 * @brief change backlight brightness to a given percentage
 * @param [in] duty value in percentage 0 ~ 100
 */
esp_err_t set_backlight_brightness(int duty);

/**
 * @brief get brightness level as a percentage value 0 ~ 100
 */
int get_backlight_brightness(void);

/**
 * @brief power off the backlight
 */
esp_err_t set_backlight_off(void);

#ifdef __cplusplus
}
#endif
#endif