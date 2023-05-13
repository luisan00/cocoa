#include "nvs_flash.h"

#include "storage.h"
#include "logger.h"

//
esp_err_t storage_init(void) {
    esp_err_t err = nvs_flash_init();
    if (err != ESP_OK) {
        loge("err: %s trying to init default partition", esp_err_to_name(err));
        return err;
    }
    return ESP_OK;
}
//
esp_err_t storage_open(const char *ns, nvs_open_mode_t m, nvs_handle_t *h) {
    esp_err_t res = nvs_open(ns, m, h);
    if (res != ESP_OK) {
        loge("Error: %s, opening nvs partition %s", esp_err_to_name(res), ns);
    }
    return res;
}

esp_err_t storage_set_u8(const char *ns, const char *k, uint8_t v) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READWRITE, &h));
    ESP_ERROR_CHECK(nvs_set_u8(h, k, v));
    ESP_ERROR_CHECK(storage_commit(h));
    nvs_close(h);
    return ESP_OK;
}
//
esp_err_t storage_set_u32(const char *ns, const char *k, uint32_t v) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READWRITE, &h));
    ESP_ERROR_CHECK(nvs_set_u32(h, k, v));
    ESP_ERROR_CHECK(storage_commit(h));
    nvs_close(h);
    return ESP_OK;
}
esp_err_t storage_set_str(const char *ns, const char *k, const char *v) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READWRITE, &h));
    ESP_ERROR_CHECK(nvs_set_str(h, k, v));
    ESP_ERROR_CHECK(storage_commit(h));
    nvs_close(h);
    return ESP_OK;
}
//
esp_err_t storage_delete_key(const char *ns, const char *k) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READWRITE, &h));
    ESP_ERROR_CHECK(nvs_erase_key(h, k));
    ESP_ERROR_CHECK(storage_commit(h));
    nvs_close(h);
    return ESP_OK;
}

esp_err_t storage_commit(nvs_handle_t h) {
    esp_err_t res = nvs_commit(h);
    if (res != ESP_OK) {
        loge("Error: %s, committing changes", esp_err_to_name(res));
    }
    return res;
}