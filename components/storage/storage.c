#include "logger.h"
#include "nvs_flash.h"

#include "storage.h"
#include "storage_internals.h"

// NOTE: esp-idf reserve the final page of nvs entries for internal use (for defrag/consolidation)
// See: https://github.com/espressif/esp-idf/issues/5247#issuecomment-1048604221
// If the 'free entries' appears to include these entries, deduct them from the value returned.
// static const size_t NUM_ALL_NVS_ENTRIES = 504;
// static const size_t NUM_ESP_RESERVED_ENTRIES = 126;

esp_err_t nvs_init(void) {
    esp_err_t err = nvs_flash_init();

    if (err != ESP_OK) {
        loge("err: %s trying to init default nvs partition", esp_err_to_name(err));
        return err;
    }
    return ESP_OK;
}