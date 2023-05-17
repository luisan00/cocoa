/*
 * Copyright (c) 2022 Mesh4all <mesh4all.org>
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
 * @ingroup storage
 * @{
 * @brief   Non Volatile Storage
 * @author  luisan00 <luisan00@hotmail.com>
 */
#ifndef STORAGE_H
#define STORAGE_H
#include <stdint.h>
#include "nvs.h"
#include "esp_err.h"
#ifdef __cplusplus
extern "C" {
#endif
esp_err_t storage_init(void);
esp_err_t storage_open(const char *ns, nvs_open_mode_t m, nvs_handle_t *h);
// save value by key
esp_err_t storage_set_u8(const char *ns, const char *k, uint8_t v);
esp_err_t storage_set_u32(const char *ns, const char *k, uint32_t v);
esp_err_t storage_set_str(const char *ns, const char *k, const char *v);
esp_err_t storage_set_blob(const char *ns, const char *k, const uint8_t *v, size_t s);
// get values by key
esp_err_t storage_get_u8(const char *ns, const char *k, uint8_t *v);
esp_err_t storage_get_u32(const char *ns, const char *k, uint32_t *v);
esp_err_t storage_get_str(const char *ns, const char *k, char *v, size_t *str_len);
esp_err_t storage_get_blob(const char *ns, const char *k, uint8_t *v, size_t *blob_len);
// delete keyed entries
esp_err_t storage_delete_key(const char *ns, const char *k);
esp_err_t storage_commit(nvs_handle_t h);
#ifdef __cplusplus
}
#endif

#endif /* STORAGE_H */
       /** @} */