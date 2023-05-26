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
 * @brief   [N]on [V]olatile [S]torage primitives
 * @author  luisan00 <luisan00@hotmail.com>
 */
#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>

#include "nvs.h"
#include "nvs_flash.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the default NVS partition
 *
 * @return One of the following:
 * | Error Code | Description                                                          |
 * |------------|----------------------------------------------------------------------|
 * | ESP_OK     | Storage was successfully initialized                                 |
 * | ESP_ERR_NVS_NO_FREE_PAGES | The NVS storage contains no empty pages               |
 * | ESP_ERR_NOT_FOUND | No partition with label “nvs” is found in the partition table |
 * | ESP_ERR_NO_MEM    | Memory could not be allocated for the internal structures     |
 *
 * Also can return:
 * - one of the error codes from the underlying flash storage driver
 * - error codes from nvs_flash_read_security_cfg API (when “NVS_ENCRYPTION” is enabled)
 * - error codes from nvs_flash_generate_keys API (when “NVS_ENCRYPTION” is enabled)
 * - error codes from nvs_flash_secure_init_partition API (when “NVS_ENCRYPTION” is enabled)
 */
esp_err_t storage_init(void);

/**
 * @brief
 *
 * @param [in] cfg
 * @return
 */
esp_err_t storage_secure_init(nvs_sec_cfg_t cfg);

/**
 * @brief Deinitialize NVS storage for the default NVS partition
 *
 * @return One of the following:
 * | Error Code | Description                                                     |
 * |------------|-----------------------------------------------------------------|
 * | ESP_OK                      | Storage was deinit successfully                |
 * | ESP_ERR_NVS_NOT_INITIALIZED | storage was not initialized prior to this call |
 */
esp_err_t storage_deinit(void);

/**
 * @brief Open non-volatile storage with a given namespace from the default NVS partition
 *
 * @param [in] ns Namespace name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1) characters.
 * @param [in] m NVS_READWRITE or NVS_READONLY. NVS_READONLY, will open a handle for read only.
 * @param [out] h If successful (return code is zero), handle will be returned in this argument.
 * @return One of the following esp_err_t response codes:
 * | Error Code | Description                                                              |
 * |------------|--------------------------------------------------------------------------|
 * | ESP_OK     | Storage handle was opened successfully                                   |
 * | ESP_FAIL   | There is an internal error; most likely corrupted NVS partition          |
 * | ESP_ERR_NVS_NOT_INITIALIZED| if the storage driver is not initialized                 |
 * | ESP_ERR_NVS_PART_NOT_FOUND | The partition with label “nvs” is not found              |
 * | ESP_ERR_NVS_NOT_FOUND      | namespace doesn’t exist yet and mode is NVS_READONLY     |
 * | ESP_ERR_NVS_INVALID_NAME   | namespace name doesn’t satisfy constraints               |
 * | ESP_ERR_NO_MEM             | Memory could not be allocated for the internal structures|
 * | ESP_ERR_NVS_NOT_ENOUGH_SPACE | There is no space for a new entry or there are too many
 * different namespaces (maximum allowed different namespaces: 254) |
 */
esp_err_t storage_open(const char *ns, nvs_open_mode_t m, nvs_handle_t *h);

//
// *** SAVE ***
//

/**
 * @brief Set uint8_t value for given key
 *
 * @param [in] ns Namespace name
 * @param [in] k The key name
 * @param [in] v The value to set
 * @return One of the following:
 * | Error Code | Description                                                     |
 * |------------|-----------------------------------------------------------------|
 * | ESP_OK     | Value was set successfully                                      |
 * | ESP_FAIL   | There is an internal error; most likely corrupted NVS partition |
 * | ESP_ERR_NVS_INVALID_HANDLE   | Handle is NULL or it was closed               |
 * | ESP_ERR_NVS_READ_ONLY        | Operation mode was read only                  |
 * | ESP_ERR_NVS_INVALID_NAME     | The given key doesn’t satisfy constraints     |
 * | ESP_ERR_NVS_NOT_ENOUGH_SPACE | Not enough space in the underlying storage    |
 * | ESP_ERR_NVS_REMOVE_FAILED    | Value wasn’t updated because flash write operation has failed |
 */
esp_err_t storage_set_u8(const char *ns, const char *k, uint8_t v);

/**
 * @brief Set uint32_t value for given key
 *
 * @param [in] ns Namespace name
 * @param [in] k The key name
 * @param [in] v The value to set
 * @return see storage_set_u8()
 */
esp_err_t storage_set_u32(const char *ns, const char *k, uint32_t v);

/**
 * @brief
 *
 * @param [in] ns Namespace name
 * @param [in] k The key name
 * @param [in] v The value to set
 * @return
 */
esp_err_t storage_set_str(const char *ns, const char *k, const char *v);

/**
 * @brief Set variable length binary value for given key
 *
 * @param [in] ns Namespace name
 * @param [in] k Key name
 * @param [in] v The value to set
 * @param [in] s Length of binary value to set, in bytes.
 * @return One of the following:
 * | Error Code | Description                                                                     |
 * |------------|---------------------------------------------------------------------------------|
 * | ESP_OK     | Value was set successfully                                                      |
 * | ESP_FAIL   | There is an internal error; most likely corrupted NVS partition                 |
 * | ESP_ERR_NVS_INVALID_HANDLE   | Handle is NULL or it was closed                               |
 * | ESP_ERR_NVS_READ_ONLY        | Operation mode was read only                                  |
 * | ESP_ERR_NVS_INVALID_NAME     | The given key doesn’t satisfy constraints                     |
 * | ESP_ERR_NVS_NOT_ENOUGH_SPACE | Not enough space in the underlying storage                    |
 * | ESP_ERR_NVS_REMOVE_FAILED    | Value wasn’t updated because flash write operation has failed |
 * | ESP_ERR_NVS_VALUE_TOO_LONG   | Value is too long, max: 508000 bytes                          |
 */
esp_err_t storage_set_blob(const char *ns, const char *k, const uint8_t *v, size_t s);

//
// *** GET ***
//

/**
 * @brief Get uint8_t value for the requested key
 *
 * @param [in] ns Namespace name
 * @param [in] k The key
 * @param [out] v pointer to hold the value
 * @return
 */
esp_err_t storage_get_u8(const char *ns, const char *k, uint8_t *v);

/**
 * @brief Get uint32_t value for the requested key
 *
 * @param [in] ns Namespace name
 * @param [in] k The key
 * @param [out] v pointer to hold the value
 * @return
 */
esp_err_t storage_get_u32(const char *ns, const char *k, uint32_t *v);

/**
 * @brief Get string value for given key
 *
 * @param [in] ns Namespace name
 * @param [in] k Key name
 * @param [out] v Pointer to the output value
 * @param [in,out] s A non-zero pointer to the variable holding the length of out_value. In case
 * out_value a zero, will be set to the length required to hold the value. Includes zero terminator
 * @return One of the following:
 * | Error Code                 | Description                                |
 * |----------------------------|--------------------------------------------|
 * | ESP_OK                     | value was retrieved successfully           |
 * | ESP_FAIL                   | Internal error, most likely due to corrupted NVS partition |
 * | ESP_ERR_NVS_NOT_FOUND      | Requested key doesn't exist                |
 * | ESP_ERR_NVS_INVALID_HANDLE | Invalid or NULL handle                     |
 * | ESP_ERR_NVS_INVALID_NAME   | The given key doesn’t satisfy constraints  |
 * | ESP_ERR_NVS_INVALID_LENGTH | The length is not sufficient to store data |
 */
esp_err_t storage_get_str(const char *ns, const char *k, char *v, size_t *s);

/**
 * @brief Get blob value for given key.
 * @note This function behaves the same as storage_get_str, except for the data type.
 *
 * @param [in] ns Namespace name
 * @param [in] k Key name
 * @param [out] v Pointer to the output value
 * @param [in,out] s A non-zero pointer to the variable holding the length of out_value
 * @return esp_err_t code as in storage_get_str()
 */
esp_err_t storage_get_blob(const char *ns, const char *k, uint8_t *v, size_t *s);

//
// *** DELETE ***
//

/**
 * @brief Erase key-value pair with given key name
 *
 * @param [in] ns namespace name
 * @param [in] k Key name. Maximum length is (NVS_KEY_NAME_MAX_SIZE-1)
 * @return One of the following:
 * | Error Code                 | Description                            |
 * |----------------------------|----------------------------------------|
 * | ESP_OK                     | erase operation was successful         |
 * | ESP_FAIL                   | There is an internal error             |
 * | ESP_ERR_NVS_INVALID_HANDLE | Handle has been closed or is NULL      |
 * | ESP_ERR_NVS_READ_ONLY      | Handle was opened as read only         |
 * | ESP_ERR_NVS_NOT_FOUND      | The requested key doesn’t exist        |
 */
esp_err_t storage_delete_key(const char *ns, const char *k);

/**
 * @brief Erase all key-value pairs in a given namespace
 *
 * @param [in] ns The namespace name
 * @return One of the following:
 * | Error Code                 | Description                            |
 * |----------------------------|----------------------------------------|
 * | ESP_OK                     | Delete operation was successful        |
 * | ESP_FAIL                   | There is an internal error             |
 * | ESP_ERR_NVS_INVALID_HANDLE | Handle has been closed or is NULL      |
 * | ESP_ERR_NVS_READ_ONLY      | Handle was opened as read only         |
 */
esp_err_t storage_delete_all(const char *ns);

// *** OTHERS ***

/**
 * @brief Write any pending changes to non-volatile storage
 *
 * @param [in] h Storage handle obtained with storage_open(). Handles that were opened read only
 * cannot be used
 * @return One of the following:
 * | Error Code                 | Description                            |
 * |----------------------------|----------------------------------------|
 * | ESP_OK                     | Changes have been written successfully |
 * | ESP_ERR_NVS_INVALID_HANDLE | Handle has been closed or is NULL      |
 */
esp_err_t storage_commit(nvs_handle_t h);

/**
 * @brief Erase a nvs partition
 * @note If the partition is initialized, this function first de-initializes it. Afterwards, the
 * partition has to be initialized again to be used.
 *
 * @param [in] name partion name or NULL for the default nvs partition
 *
 * @return One of the following:
 * | Error Code                 | Description                                                  |
 * |:---------------------------|:-------------------------------------------------------------|
 * | ESP_OK                     | Flash erase operation was successful                         |
 * | ESP_ERR_NOT_FOUND          | There is no default nvs partition or with the given name     |
 */
esp_err_t storage_flash_erase(const char *partition);

/**
 * @brief Get information about number of used entries, free entries, total entries, and amount
 * namespace in partition
 *
 * @param [in] partition name of the partition or NULL for the default nvs partition
 * @param [out] stats
 *
 * @return one of the following **esp_err_t** codes:
 * | Error Code                  | Description                                              |
 * |:----------------------------|:---------------------------------------------------------|
 * | ESP_OK                      | Return param nvs_stats will be filled                    |
 * | ESP_ERR_NVS_PART_NOT_FOUND  | Default partition or with label [partition] is not found |
 * | ESP_ERR_NVS_NOT_INITIALIZED | Storage driver is not initialized        |
 * | ESP_ERR_INVALID_ARG         | [stats] equal to NULL                    |
 * | ESP_ERR_INVALID_STATE       | There is page with the status of INVALID |
 */
esp_err_t storage_stats(const char *partition, nvs_stats_t *stats);

/**
 * @brief Get the number of entries in the given namespace
 * @param [in] ns The namespace name
 * @param [out] used_entries number of entries in the given namespace
 *
 * @return One of the following **esp_err_t** codes:
 * | Error Code                  | Description                              |
 * |:----------------------------|:-----------------------------------------|
 * | ESP_OK                      | Return param used_entries will be filled |
 * | ESP_ERR_NVS_NOT_INITIALIZED | Storage driver is not initialized        |
 * | ESP_ERR_NVS_INVALID_HANDLE  | If handle has been closed or is NULL     |
 * | ESP_ERR_INVALID_ARG         | Used entries is NULL                     |
 */
esp_err_t storage_used_entry_count(const char *ns, size_t *used_entries);

#ifdef __cplusplus
}
#endif

#endif /* STORAGE_H */
/** @} */
