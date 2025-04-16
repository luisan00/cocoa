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
 * @brief   lcd config
 * @author  luisan00 <luisan00@hotmail.com>
 * @ingroup screen
 * @{
 */

 #ifndef LCD_H
 #define LCD_H
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 #include "lvgl.h"
 #include "esp_lvgl_port.h"
 
 
 /**
  * @brief PCLK limitation of PSRAM bandwidt : 2-17
  */
 #define LCD_PIXEL_CLOCK_HZ (2 * 1000 * 1000)
 
 /**
  * @brief
  * @{
  */
 #define LCD_BL_LIGHT_ON 1                 /*!> backlight power on*/
 #define LCD_BL_LIGHT_OFF !LCD_BL_LIGHT_ON /*!> backlight power off*/
 //
 #define LCD_PWR_ON 1            /*!> Screen power on*/
 #define LCD_PWR_OFF !LCD_PWR_ON /*!> screen power off */
 /** @} */
 
 /**
  * @brief Conection requires 8 bit parallel interface
  * @{
  */
 #define LCD_DATA0 39 /*!> DATA0 wired to pin 39 on the MCU */
 #define LCD_DATA1 40 /*!> DATA1 wired to pin 40 on the MCU */
 #define LCD_DATA2 41 /*!> DATA2 wired to pin 41 on the MCU */
 #define LCD_DATA3 42 /*!> DATA3 wired to pin 42 on the MCU */
 #define LCD_DATA4 45 /*!> DATA4 wired to pin 45 on the MCU */
 #define LCD_DATA5 46 /*!> DATA5 wired to pin 46 on the MCU */
 #define LCD_DATA6 47 /*!> DATA6 wired to pin 47 on the MCU */
 #define LCD_DATA7 48 /*!> DATA7 wired to pin 48 on the MCU */
 /** @} */
 
 #define LCD_PWR 15 /*!> Power on pin */
 
 #define LCD_RST 5 /*!> Reset pin */
 #define LCD_CS 6  /*!> CS pin */
 #define LCD_DC 7  /*!> DC pin*/
 #define LCD_WR 8  /*!> WR pin */
 #define LCD_RD 9  /*!> RD pin  */
 
 #define LCD_BL 38 /*!> Backlight pin */
 
 #define LCD_H_RES 320 /*!> Horiz. resolution is 320 dots */
 #define LCD_V_RES 170 /*!> Vertical resolution is 170 dots */
 
 #define LCD_CMD_BITS 8   /*!> use 8 bits per command */
 #define LCD_PARAM_BITS 8 /*!> use 8 bits per param */
 
 // LVGL
 // best to keep this as is (1/10th of the display pixels)
 #define LVGL_BUFFER_SIZE        (((LCD_H_RES * LCD_V_RES) / 10) + LCD_H_RES)
 // LVGL Timer options
 #define LVGL_TICK_PERIOD_MS    5
 #define LVGL_MAX_SLEEP_MS      (LVGL_TICK_PERIOD_MS * 2) // this affects how fast the screen is refreshed
 #define LVGL_TASK_STACK_SIZE   (4 * 1024)
 #define LVGL_TASK_PRIORITY     2
 
 // fixup!
 //#ifndef LV_COLOR_16_SWAP
 //#define LV_COLOR_16_SWAP lv_draw_sw_rgb565_swap(px_map, lv_area_get_size(&offset_area))
 //#endif
 
 /**
  * @brief
  * @return [esp_err_t] error
  */
 esp_err_t lcd_brightness_init();
 esp_err_t lcd_brightness_set(int brightness_percent);
 esp_err_t lcd_backlight_on();
 esp_err_t lcd_backlight_off();
 /**
  * @brief 
  * @param disp_drv
  * @param disp_handle
  * @param [in] backlight_on 
  */
 esp_err_t lcd_init(lv_disp_drv_t disp_drv, lv_disp_t **disp_handle, bool backlight_on);
 
 
 #ifdef __cplusplus
 } 
 #endif // extern C
 #endif // LCD_CONFIG_H
 /** @} */
 