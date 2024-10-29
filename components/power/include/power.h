/*
 * Copyright (c) 2023-2024 Luis A. Ruiz <luisan00@hotmail.com>
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
 * @brief power section, setup and routines
 * @author  luisan00 <luisan00@hotmail.com>
 * @ingroup power
 * @{
 */
#ifndef POWER_H
#define POWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "esp_err.h"

// T-Display Battery Voltage
#define BAT_PIN_NUM_VOLT 4         // (ADC_UNIT_1, ADC_CHANNEL_3) -  LCD_BAT_VOLT
#define NO_BAT_MILLIVOLTS 4500     // greater than 4600 no battery connected
#define BAT_CHARGE_MILLIVOLTS 4350 // greater than 4350 means charging

/**
 * @brief
 */
esp_err_t init_battery_adc(void);

/**
 * @brief
 */
esp_err_t init_battery_monitor(void);

// return mV
int get_battery_voltage(void);

/**
 * @brief check if USB is connected and return:
 * | ID | mean         | Description                             |
 * |---:|:--------------|:----------------------------------------|
 * |  1 | Connected     | Power throw USB connector detected      |
 * |  0 | Not Connected | Power throw USB connector not detetcted |
 * | -1 | Error         | Bad things :-p                          |
 *
 */
int usb_power_connected(void);

#ifdef __cplusplus
}
#endif //

#endif //
       /** @} */