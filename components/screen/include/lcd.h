#ifndef LCD_H
#define LCD_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// Bit number used to represent command and parameter
#define LCD_CMD_BITS 8
#define LCD_PARAM_BITS 8

#define LVGL_TICK_PERIOD_MS 2
#define LVGL_TASK_MAX_DELAY_MS 500
#define LVGL_TASK_MIN_DELAY_MS 1
#define LVGL_TASK_STACK_SIZE (4 * 1024)
#define LVGL_TASK_PRIORITY 2
#define DMA_BURST_SIZE 64

esp_err_t init_i80_bus();

#ifdef __cplusplus
}
#endif

#endif // LCD_H