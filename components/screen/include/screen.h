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
extern "C"
{
#endif

#define ST7789_DRIVER
    // #define INIT_SEQUENCE_3 // Using this initialisation sequence improves the display image

#define CGRAM_OFFSET
// #define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
#define TFT_RGB_ORDER TFT_BGR // Colour order Blue-Green-Red

#define TFT_INVERSION_ON
    // #define TFT_INVERSION_OFF

#define TFT_PARALLEL_8_BIT

#ifdef __cplusplus
}
#endif // __cplusplus
#endif
/** @} */