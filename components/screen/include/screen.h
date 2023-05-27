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
 * @brief   screen utilities
 * @author  luisan00 <luisan00@hotmail.com>
 * @ingroup screen
 * @{
 */
#ifndef SCREEN_H
#define SCREEN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"

/**
 *
 * @brief   define colors as 32 bits unsigned integer RGB order,
 *          0x00, 0x00, 0x00 -> 0x000000
 */
#define COLOR_BLACK 0x000000U /*!> black */
#define COLOR_WHITE 0xffffffU /*!> white */

#define COLOR_GREY 0x7f7f7fU /*!> grey 50% */

#define COLOR_RED 0xff0000U   /*!> red */
#define COLOR_GREEN 0x00ff00U /*!> green */
#define COLOR_BLUE 0x0000ffU  /*!> blue */

/**
 * @brief
 */
esp_err_t screen_init(void);

#ifdef __cplusplus
}
#endif

#endif
/** @} */