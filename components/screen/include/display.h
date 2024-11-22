/**
 * Copyright (c) 2023-2024 luisan00 <luisan00@hotmail.com>
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
 * @brief   display config
 * @author  luisan00 <luisan00@hotmail.com>
 * @ingroup screen
 * @{
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CONFIG_BOARD_QEMU)
#include "qemu_display.h"
#elif defined(CONFIG_BOARD_TDISPLAYS3)
#include "tdisplays3_display.h"
#elif defined(CONFIG_BOARD_TDISPLAYS3PRO)
#include "tdisplays3pro_display.h"
#else
// option
#endif

#ifdef __cplusplus
}
#endif // extern C

#endif // DISPLAY_H
/** @} */
