#ifndef GUI_H
#define GUI_H

#include "esp_err.h"
/**
 *
 * @brief   define colors as 32 bits unsigned integer RGB order,
 *          0x00, 0x00, 0x00 -> 0x000000
 */
#define COLOR_WHITE 0xffffffU /*!> white */
#define COLOR_BLACK 0x000000U /*!> black */

#define COLOR_GRAY_75 0xbebebeU /*!> grey 75 % */
#define COLOR_GRAY_50 0x7f7f7fU /*!> grey 50 % */
#define COLOR_GRAY_25 0x3f3f3fU /*!> grey 25 % */

#define COLOR_RED 0xff0000U   /*!> full red */
#define COLOR_GREEN 0x00ff00U /*!> full green */
#define COLOR_BLUE 0x0000ffU  /*!> full blue */

void gui_init(lv_obj_t *screen);
void gui_deinit(void);

#endif /* GUI_H */