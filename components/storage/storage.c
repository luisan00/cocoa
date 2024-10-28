#include <string.h>
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
esp_err_t storage_secure_init(nvs_sec_cfg_t cfg) {
    // ToDo
    return ESP_FAIL;
}

//
esp_err_t storage_deinit(void) {
    // ToDo
    return ESP_FAIL;
}

//
esp_err_t storage_open(const char *ns, nvs_open_mode_t m, nvs_handle_t *h) {
    esp_err_t res = nvs_open(ns, m, h);
    if (res != ESP_OK) {
        loge("Error: %s, opening nvs partition %s", esp_err_to_name(res), ns);
    }
    return res;
}

//
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

//
esp_err_t storage_set_str(const char *ns, const char *k, const char *v) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READWRITE, &h));
    ESP_ERROR_CHECK(nvs_set_str(h, k, v));
    ESP_ERROR_CHECK(storage_commit(h));
    nvs_close(h);
    return ESP_OK;
}

//
esp_err_t storage_set_blob(const char *ns, const char *k, const uint8_t *v, size_t s) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READWRITE, &h));
    ESP_ERROR_CHECK(nvs_set_blob(h, k, v, s));
    ESP_ERROR_CHECK(storage_commit(h));
    nvs_close(h);
    return ESP_OK;
}

//
esp_err_t storage_get_u8(const char *ns, const char *k, uint8_t *v) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READONLY, &h));
    esp_err_t res = nvs_get_u8(h, k, v);
    if (res == ESP_ERR_NVS_NOT_FOUND) {
        loge("storage_get_u8() for %s not found", k);
        nvs_close(h);
        return res;
    }
    nvs_close(h);
    return res;
}

//
esp_err_t storage_get_u32(const char *ns, const char *k, uint32_t *v) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READONLY, &h));
    esp_err_t res = nvs_get_u32(h, k, v);
    if (res == ESP_ERR_NVS_NOT_FOUND) {
        loge("storage_get_u32() for %s not found", k);
        nvs_close(h);
        return res;
    }
    nvs_close(h);
    return res;
}

//
esp_err_t storage_get_str(const char *ns, const char *k, char *str, size_t *s) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READONLY, &h));
    esp_err_t res = nvs_get_str(h, k, NULL, s);
    if (res == ESP_ERR_NVS_NOT_FOUND) {
        loge("get_str() for %s not found", k);
        nvs_close(h);
        return res;
    }
    res = nvs_get_str(h, k, str, s);
    if (res != ESP_OK) {
        loge("get_str() for %s fail: %s", k, esp_err_to_name(res));
        nvs_close(h);
        return res;
    }
    nvs_close(h);
    return res;
}

//
esp_err_t storage_get_blob(const char *ns, const char *k, uint8_t *v, size_t *s) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READONLY, &h));
    esp_err_t res = nvs_get_blob(h, k, NULL, s);
    if (res == ESP_ERR_NVS_NOT_FOUND) {
        loge("get_blob() for %s not found", k);
        nvs_close(h);
        return res;
    }
    res = nvs_get_blob(h, k, v, s);
    if (res != ESP_OK) {
        loge("get_blob() for %s fail: %s", k, esp_err_to_name(res));
        nvs_close(h);
        return res;
    }
    nvs_close(h);
    return res;
}

//
esp_err_t storage_delete_key(const char *ns, const char *k) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READWRITE, &h));
    esp_err_t res = nvs_erase_key(h, k);
    if (res == ESP_ERR_NVS_NOT_FOUND) {
        loge("storage_delete_key() for %s not found", k);
        nvs_close(h);
        return res;
    }
    ESP_ERROR_CHECK(storage_commit(h));
    nvs_close(h);
    return res;
}

//
esp_err_t storage_delete_all(const char *ns) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READWRITE, &h));
    esp_err_t res = nvs_erase_all(h);
    if (res != ESP_OK) {
        loge("storage_delete_all(): %s", esp_err_to_name(res));
        nvs_close(h);
    }
    ESP_ERROR_CHECK(storage_commit(h));
    nvs_close(h);
    return res;
}

//
esp_err_t storage_commit(nvs_handle_t h) {
    esp_err_t res = nvs_commit(h);
    if (res != ESP_OK) {
        loge("Error: %s, committing changes", esp_err_to_name(res));
    }
    return res;
}

// Erase the default NVS partition
esp_err_t storage_flash_erase(const char *partition) {
    // if no name then erase default nvs partition
    esp_err_t res;
    if (partition == NULL) {
        res = nvs_flash_erase();
    } else {
        res = nvs_flash_erase_partition(partition);
    }

    if (res != ESP_OK) {
        loge("storage_flash_erase(): %s", esp_err_to_name(res));
    }
    return res;
}

//
esp_err_t storage_stats(const char *partition, nvs_stats_t *stats) {
    esp_err_t res = nvs_get_stats(NULL, stats);
    if (res != ESP_OK) {
        loge("storage_stats() for partition %s: %s ", partition, esp_err_to_name(res));
    }
    return res;
}

//
esp_err_t storage_used_entry_count(const char *ns, size_t *used_entries) {
    nvs_handle_t h;
    ESP_ERROR_CHECK(storage_open(ns, NVS_READWRITE, &h));
    esp_err_t res = nvs_get_used_entry_count(h, used_entries);
    if (res != ESP_OK) {
        loge("_used_entry_count() %s for namespace %s", esp_err_to_name(res), ns);
    }
    nvs_close(h);
    return res;
}
