/*
 * Copyright (c) 2023 Luis A. Ruiz <luisan00@hotmail.com>
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
 * @brief logging macros
 * @{
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <string.h>
#include "esp_log.h"

/**
 * @name
 * @{
 */
#define loge(fmt, ...) ESP_LOGE(basename(__FILE__), "L%d: " fmt, __LINE__, ##__VA_ARGS__)
#define logw(fmt, ...) ESP_LOGW(basename(__FILE__), "L%d: " fmt, __LINE__, ##__VA_ARGS__)
#define logi(fmt, ...) ESP_LOGI(basename(__FILE__), "L%d: " fmt, __LINE__, ##__VA_ARGS__)
#define logd(fmt, ...) ESP_LOGD(basename(__FILE__), "L%d: " fmt, __LINE__, ##__VA_ARGS__)
#define logv(fmt, ...) ESP_LOGV(basename(__FILE__), "L%d: " fmt, __LINE__, ##__VA_ARGS__)
/** @} */
#endif
/** @] */