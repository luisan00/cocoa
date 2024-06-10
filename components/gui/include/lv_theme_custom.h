#ifndef LV_THEME_CUSTOM_H
#define LV_THEME_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl.h"
/**
 *
 * @brief   define colors as 32 bits unsigned integer RGB order,
 *          0x00, 0x00, 0x00 -> 0x000000
 */
#define COLOR_WHITE lv_color_white() /*!> white */
#define COLOR_BLACK lv_color_black() /*!> black */

void custom_theme_init(void);

#ifdef __cplusplus
}
#endif

#endif /*LV_THEME_BASIC_H*/
