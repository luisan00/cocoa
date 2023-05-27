/**
 * Copyright (c) 2023 luisan00 <luisan00@hotmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @brief   screen config
 * @author  luisan00 <luisan00@hotmail.com>
 * @ingroup screen
 * @{
 */

#ifndef SCREEN_CONFIG_H
#define SCREEN_CONFIG_H

/**
 * @brief
 */
#define SCREEN_PX_CLOCK_HZ (6528000) /*!> EXAMPLE_LCD_PIXEL_CLOCK_HZ */

/**
 * @brief
 * @{
 */
#define SCREEN_BK_LIGHT_ON 1                    /*!> backlight power on*/
#define SCREEN_BK_LIGHT_OFF !SCREEN_BK_LIGHT_ON /*!> backlight power off*/

#define SCREEN_PWR_ON 1               /*!> Screen power on*/
#define SCREEN_PWR_OFF !SCREEN_PWR_ON /*!> screen power off */
/** @} */

/**
 * @brief Conection requires 8 bit parallel interface
 * @{
 */
#define SCREEN_DATA0 39 /*!> DATA0 wired to pin 39 on the MCU */
#define SCREEN_DATA1 40 /*!> DATA1 wired to pin 40 on the MCU */
#define SCREEN_DATA2 41 /*!> DATA2 wired to pin 41 on the MCU */
#define SCREEN_DATA3 42 /*!> DATA3 wired to pin 42 on the MCU */
#define SCREEN_DATA4 45 /*!> DATA4 wired to pin 45 on the MCU */
#define SCREEN_DATA5 46 /*!> DATA5 wired to pin 46 on the MCU */
#define SCREEN_DATA6 47 /*!> DATA6 wired to pin 47 on the MCU */
#define SCREEN_DATA7 48 /*!> DATA7 wired to pin 48 on the MCU */
/** @} */

#define SCREEN_PWR 15        /*!> Power on/off the display */
#define SCREEN_WR GPIO_NUM_8 /*!> WR pin */
#define SCREEN_RD GPIO_NUM_9 /*!> RD pin  */
#define SCREEN_CS 6          /*!> CS pin */
#define SCREEN_DC 7          /*!> DC pin*/
#define SCREEN_RST 5         /*!> Reset pin */
#define SCREEN_BK_LIGHT 38   /*!> Control the display backlight  */

/**
 * @brief The pixel number in horizontal and vertical
 * @{
 */
#define SCREEN_H_RES 320                                /*!> Horiz. resolution is 320 dots */
#define SCREEN_V_RES 170                                /*!> Vertical resolution is 170 dots */
#define LVGL_LCD_BUF_SIZE (SCREEN_H_RES * SCREEN_V_RES) /*!> Then LVGL require a 320*170 buffer size */
/** @} */

/**
 * @brief  number used to represent command and parameter
 * @{
 */
#define SCREEN_CMD_BITS 8   /*!>*/
#define SCREEN_PARAM_BITS 8 /*!>*/
/** @} */

/**
 * @brief
 */
#define SCREEN_LVGL_TICK_PERIOD_MS 2

/**
 * @brief The back light can be controlled by PWM, it's done using the LEDC API.
 * 4095 =  50%
 * 8190 = 100%
 * @{
 */
#define LEDC_TIMER LEDC_TIMER_0                    /*!> Timer 0 will be used for this purpose */
#define LEDC_MODE LEDC_LOW_SPEED_MODE              /*!> Speed mode */
#define LEDC_CHANNEL LEDC_CHANNEL_0                /*!> Channel */
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT            /*!> Set duty resolution to 13 bits */
#define LEDC_DUTY(x) ((2 * LEDC_DUTY_RES) - 1) * x /*!> (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095 */
#define LEDC_FREQUENCY (5000)                      // Frequency in Hertz. Set frequency at 5 kHz
/** @} */

#endif // SCREEN_CONFIG_H
/** @} */
