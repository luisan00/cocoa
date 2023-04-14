
#ifndef STORAGE_H
#define STORAGE_H

#include "esp_err.h"
#include "nvs_flash.h"
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief initialize the default NVS partition
     *
     * @return esp_err_t ESP_OK: succeed, ESP_(others): fail
     */
    esp_err_t nvs_init(void);

    /**
     * @brief store a key/value pair in the NVS using the given namespace
     *
     * @param [in] namespace
     * @param [in] key
     * @param [out] value uint8_t value to store
     * @return esp_err_t ESP_OK: succeed, ESP_(others): fail
     */
    esp_err_t nvs_set_uint8(const char *namespace, const char *key, uint8_t value);

    /**
     * @brief store a key/value pair in the NVS using the given namespace
     *
     * @param namespace
     * @param key
     * @param value uint32_t value to store
     * @return esp_err_t ESP_OK: succeed, ESP_(others): fail
     */
    esp_err_t nvs_set_uint32(const char *namespace, const char *key, uint32_t value);

    /**
     * @brief Store a c string in the NVS using the given namespace and key
     *
     * @param [in] namespace
     * @param [in] key
     * @param [in] value
     * @return esp_err_t ESP_OK: succeed, ESP_(others): fail
     */
    esp_err_t nvs_set_string(const char *namespace, const char *key, const char *value);

    /**
     * @brief Get the value as uint8_t with key [key] from the NVS using the given namespace
     *
     * @param [in] namespace
     * @param [in] key
     * @param [out] value
     * @return esp_err_t ESP_OK: succeed, ESP_(others): fail
     */
    esp_err_t nvs_get_uint8(const char *namespace, const char *key, uint8_t *value);

    /**
     * @brief Get the value as uint32_t with key [key] from the NVS using the given namespace
     *
     * @param [in] namespace
     * @param [in] key
     * @param [out] value pointer to the uint32_t value
     * @return esp_err_t ESP_OK: succeed, ESP_(others): fail
     */
    esp_err_t nvs_get_uint32(const char *namespace, const char *key, uint32_t *value);

    /**
     * @brief Get the value as c string with key [key] from the NVS using the given namespace
     *
     * @param [in] namespace
     * @param [in] key
     * @param [out] buffer
     * @param [out] length
     * @return esp_err_t
     */
    esp_err_t nvs_get_string(const char *namespace, const char *key, char *buffer, size_t *length);

#ifdef __cplusplus
}
#endif

#endif /* STORAGE_H */