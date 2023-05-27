
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "unity.h"

#include "storage.h"
#include "helpers.h"
#include "logger.h"

#include "test_storage.h"

static const char tag[] = "[storage]";
static const char ns[] = "ns_test";

TEST_CASE("NVS init", tag) { TEST_ASSERT_EQUAL(0, storage_init()); }

// storage_stats
TEST_CASE("storage_stats() after init should work", tag) {
    logi("storage_stats()");
    nvs_stats_t stats;
    esp_err_t res = storage_stats(NULL, &stats);
    TEST_ASSERT_EQUAL_INT(ESP_OK, res);
    // At this point the statistics for default nvs should contain the following 
    // information about entries:
    //      used:   0
    //      free:  756
    //      total: 756
    TEST_ASSERT_EQUAL_INT(0, stats.used_entries);
    TEST_ASSERT_EQUAL_INT(756, stats.free_entries);
    TEST_ASSERT_EQUAL_INT(756, stats.total_entries);
}

// save -- should work
TEST_CASE("Save should work", tag) {
    logi("storage_set_u8()");
    for (size_t i = 0; i < ARRAY_SIZEOF(u8_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_set_u8(ns, u8_data[i].key, u8_data[i].value));
    }
    logi("storage_set_u32()");
    for (size_t i = 0; i < ARRAY_SIZEOF(u32_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_set_u32(ns, u32_data[i].key, u32_data[i].value));
    }
    logi("storage_set_str()");
    for (size_t i = 0; i < ARRAY_SIZEOF(str_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_set_str(ns, str_data[i].key, str_data[i].value));
    }
    logi("storage_set_blob()");
    for (size_t i = 0; i < ARRAY_SIZEOF(blob_data); i++) {
        esp_err_t res = storage_set_blob(ns, blob_data[i].key, fromhex(blob_data[i].value),
                                         strlen(blob_data[i].value) / 2);
        TEST_ASSERT_EQUAL_INT(0, res);
    }
}

// read -- should work
TEST_CASE("Read should work", tag) {
    logi("storage_get_u8()");
    for (size_t i = 0; i < ARRAY_SIZEOF(u8_data); i++) {
        uint8_t v;
        TEST_ASSERT_EQUAL(0, storage_get_u8(ns, u8_data[i].key, &v));
        TEST_ASSERT_EQUAL(u8_data[i].value, v);
    }
    logi("storage_get_u32()");
    for (size_t i = 0; i < ARRAY_SIZEOF(u32_data); i++) {
        uint32_t v;
        TEST_ASSERT_EQUAL(0, storage_get_u32(ns, u32_data[i].key, &v));
        TEST_ASSERT_EQUAL(u32_data[i].value, v);
    }
    logi("storage_get_str()");
    for (size_t i = 0; i < ARRAY_SIZEOF(str_data); i++) {
        char *ptr = (char *)calloc(512, sizeof(char));
        size_t str_len;
        // 1. if ok
        TEST_ASSERT_EQUAL(0, storage_get_str(ns, str_data[i].key, ptr, &str_len));
        // 2. if equal length, including \0
        TEST_ASSERT_EQUAL(strlen(str_data[i].value) + 1, str_len);
        // 3. if equal string
        TEST_ASSERT_EQUAL_STRING(str_data[i].value, ptr);
        free(ptr);
    }
    logi("storage_get_blob()");
    for (size_t i = 0; i < ARRAY_SIZEOF(blob_data); i++) {
        uint8_t *ptr = (uint8_t *)calloc(512, sizeof(uint8_t));
        size_t blob_size;
        // 1. if ok
        TEST_ASSERT_EQUAL_INT(0, storage_get_blob(ns, blob_data[i].key, ptr, &blob_size));
        ptr = (uint8_t *)realloc(ptr, blob_size);
        // 2. if equal length, including
        TEST_ASSERT_EQUAL_INT(strlen(blob_data[i].value) / 2, blob_size);
        // 3. if equal values
        TEST_ASSERT_EQUAL_UINT8_ARRAY(fromhex(blob_data[i].value), ptr,
                                      strlen(blob_data[i].value) / 2);
        free(ptr);
    }
}
// delete the first entry for each data type -- should work
TEST_CASE("Delete the first entry of each datatype [should work]", tag) {
    logi("storage_delete_key()");
    TEST_ASSERT_EQUAL(0, storage_delete_key(ns, u8_data[0].key));
    TEST_ASSERT_EQUAL(0, storage_delete_key(ns, u32_data[0].key));
    TEST_ASSERT_EQUAL(0, storage_delete_key(ns, str_data[0].key));
    TEST_ASSERT_EQUAL(0, storage_delete_key(ns, blob_data[0].key));
}

// Delete some previously deleted registers -- should FAIL
TEST_CASE("Delete first entry of each datatype [should fail]", tag) {
    logi("storage_delete_key()");
    TEST_ASSERT_EQUAL(ESP_ERR_NVS_NOT_FOUND, storage_delete_key(ns, u8_data[0].key));
    TEST_ASSERT_EQUAL(ESP_ERR_NVS_NOT_FOUND, storage_delete_key(ns, u32_data[0].key));
    TEST_ASSERT_EQUAL(ESP_ERR_NVS_NOT_FOUND, storage_delete_key(ns, str_data[0].key));
    TEST_ASSERT_EQUAL(ESP_ERR_NVS_NOT_FOUND, storage_delete_key(ns, blob_data[0].key));
}
// storage_stats
TEST_CASE("storage_stats() should work", tag) {
    logi("storage_stats()");
    nvs_stats_t stats;
    esp_err_t res = storage_stats(NULL, &stats);
    TEST_ASSERT_EQUAL_INT(ESP_OK, res);
    // At this point the statistics should contain the following information about entries:
    // used:   25
    // free:  731
    // total: 756
    TEST_ASSERT_EQUAL_INT(25, stats.used_entries);
    TEST_ASSERT_EQUAL_INT(731, stats.free_entries);
    TEST_ASSERT_EQUAL_INT(756, stats.total_entries);
}

// delete all keyed entries in the given namespace
TEST_CASE("Delete all entries in a namespace", tag) {
    logi("storage_delete_all()");
    TEST_ASSERT_EQUAL_INT(ESP_OK, storage_delete_all(ns));
}

// erase default flash partition
TEST_CASE("Erase default flash partition", tag) {
    logi("storage_flash_erase()");
    TEST_ASSERT_EQUAL_INT(ESP_OK, storage_flash_erase(NULL));
}
