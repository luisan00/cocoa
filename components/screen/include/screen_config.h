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

/* LCD PANEL CONFIG */
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ (6528000) //(10 * 1000 * 1000)

// The pixel number in horizontal and vertical
#define SCR_H_RES 320
#define SCR_V_RES 170

#define LVGL_LCD_BUF_SIZE (SCR_H_RES * SCR_V_RES)
#define EXAMPLE_PSRAM_DATA_ALIGNMENT 64

/* ESP32S3 */
#define SCR_BL 38

#define SCR_D0 39
#define SCR_D1 40
#define SCR_D2 41
#define SCR_D3 42
#define SCR_D4 45
#define SCR_D5 46
#define SCR_D6 47
#define SCR_D7 48

#define SCR_RST 5
#define SCR_CS 6
#define SCR_DC 7
#define SCR_WR 8
#define SCR_RD 9

#define SCR_POWER_ON 15

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY(x)            ((2*LEDC_DUTY_RES) -1) * x //  (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY          (5000) // Frequency in Hertz. Set frequency at 5 kHz

// 4095 =  50%
// 8190 = 100%
#endif /** SCREEN_CONFIG_H */
       /** @} */