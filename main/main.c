
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  main1.c
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Aug 20, 2022
 * @brief   		:
 *
 ******************************************************************************/

/* INCLUDES ------------------------------------------------------------------*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_log.h"
#include "screen.h"

static const char *TAG = __FILE__;

void app_main(void)
{
    esp_err_t res = screen_init();
    
    if (res != ESP_OK)
    {
        ESP_LOGE(TAG, "Trying to start the display, Error: %s", esp_err_to_name(res));
    }
}