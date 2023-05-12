#include "esp_log.h"
#include "nvs_flash.h"
#include "storage.h"

static const char tag[] = "storage";

// init
esp_err_t nvs_init(void)
{
    esp_err_t err = nvs_flash_init();

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Fail %s, Initializing default NVS partition", esp_err_to_name(err));
        return err;
    }

    ESP_LOGD(tag, "Succeed ESP_OK");
    return ESP_OK;
}
// deinit
esp_err_t nvs_deinit(void)
{
    esp_err_t err = nvs_flash_deinit();
    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Fail %s, Deinitializing default NVS partition", esp_err_to_name(err));
        return err;
    }

    ESP_LOGD(tag, "Succeed ESP_OK");
    return ESP_OK;
}

// delete key/value
esp_err_t nvs_delete_key(const char *namespace, const char *key)
{
    nvs_handle_t handle;

    esp_err_t err = nvs_open(namespace, NVS_READWRITE, &handle);

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error: %s, trying to open the namespace %s", esp_err_to_name(err), namespace);
        return err;
    }
    err = nvs_erase_key(handle, key);
    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error: %s, Deleting key: %s", esp_err_to_name(err), key);
        nvs_close(handle);
        return err;
    }
    err = nvs_commit(handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error: %s, committing changes", esp_err_to_name(err));
    }

    nvs_close(handle);
    return ESP_OK;
}

// store  a single byte as uint8_t
esp_err_t nvs_set_uint8(const char *namespace, const char *key, uint8_t value)
{

    nvs_handle_t handle;

    esp_err_t err = nvs_open(namespace, NVS_READWRITE, &handle);

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error: %s, trying to open the namespace %s", esp_err_to_name(err), namespace);
        return err;
    }

    err = nvs_set_u8(handle, key, value);

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error: %s, setting the key: %s with value: %d", esp_err_to_name(err), key, value);
        nvs_close(handle);
        return err;
    }

    err = nvs_commit(handle);

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error: %s, committing changes", esp_err_to_name(err));
    }

    nvs_close(handle);
    return ESP_OK;
}

// set uint32
esp_err_t nvs_set_uint32(const char *namespace, const char *key, uint32_t value)
{

    nvs_handle_t handle;

    esp_err_t err = nvs_open(namespace, NVS_READWRITE, &handle);

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error: %s, trying to open the namespace %s", esp_err_to_name(err), namespace);
        return err;
    }

    err = nvs_set_u32(handle, key, value);

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error: %s, setting the key: %s with value: %d", esp_err_to_name(err), key, value);
        nvs_close(handle);
        return err;
    }

    err = nvs_commit(handle);

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error: %s, committing changes", esp_err_to_name(err));
    }

    nvs_close(handle);
    return ESP_OK;
}

// get uint8_t
esp_err_t nvs_get_uint8(const char *namespace, const char *key, uint8_t *value)
{
    nvs_handle_t handle;

    esp_err_t err = nvs_open(namespace, NVS_READONLY, &handle);

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error %s: trying to open the namespace %s", esp_err_to_name(err), namespace);
        return err;
    }

    err = nvs_get_u8(handle, key, value);

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error %s: getting the value for key %s", esp_err_to_name(err), key);
        nvs_close(handle);
        return err;
    }

    nvs_close(handle);
    return ESP_OK;
}

esp_err_t nvs_get_uint32(const char *namespace, const char *key, uint32_t *value)
{
    nvs_handle_t handle;

    esp_err_t err = nvs_open(namespace, NVS_READONLY, &handle);

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error %s: trying to open the namespace %s", esp_err_to_name(err), namespace);
        return err;
    }

    err = nvs_get_u32(handle, key, value);

    if (err != ESP_OK)
    {
        ESP_LOGE(tag, "Error %s: getting the value for key %s", esp_err_to_name(err), key);
        nvs_close(handle);
        return err;
    }

    nvs_close(handle);

    return ESP_OK;
}