
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

// save registers -- should work
TEST_CASE("Save should work", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(u8_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_set_u8(ns, u8_data[i].key, u8_data[i].value));
    }
    for (size_t i = 0; i < ARRAY_SIZEOF(u32_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_set_u32(ns, u32_data[i].key, u32_data[i].value));
    }
    for (size_t i = 0; i < ARRAY_SIZEOF(str_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_set_str(ns, str_data[i].key, str_data[i].value));
    }
    for (size_t i = 0; i < ARRAY_SIZEOF(blob_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_set_blob(ns, blob_data[i].key, fromhex(blob_data[i].value),
                                              strlen(blob_data[i].value) / 2));
    }
}
// Get registers -- should work
TEST_CASE("Read should work", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(u8_data); i++) {
        uint8_t v;
        TEST_ASSERT_EQUAL(0, storage_get_u8(ns, u8_data[i].key, &v));
        TEST_ASSERT_EQUAL(u8_data[i].value, v);
    }
    for (size_t i = 0; i < ARRAY_SIZEOF(u32_data); i++) {
        uint32_t v;
        TEST_ASSERT_EQUAL(0, storage_get_u32(ns, u32_data[i].key, &v));
        TEST_ASSERT_EQUAL(u32_data[i].value, v);
    }
    for (size_t i = 0; i < ARRAY_SIZEOF(str_data); i++) {
        char *ptr = (char *)malloc(512 * sizeof(char));
        size_t str_len;
        // 1. if ok
        TEST_ASSERT_EQUAL(0, storage_get_str(ns, str_data[i].key, ptr, &str_len));
        // 2. if equal length, including \0
        TEST_ASSERT_EQUAL(strlen(str_data[i].value) + 1, str_len);
        // 3. if equal string
        TEST_ASSERT_EQUAL_STRING(str_data[i].value, ptr);
        free(ptr);
    }
    for (size_t i = 0; i < ARRAY_SIZEOF(blob_data); i++)
    {
        uint8_t *ptr = (uint8_t *)malloc(512 * sizeof(uint8_t));
        size_t blob_size;
        // 1. if ok
        TEST_ASSERT_EQUAL(0, storage_get_blob(ns, blob_data[i].key, ptr, &blob_size));
        // 2. if equal length, including \0
        TEST_ASSERT_EQUAL(strlen(blob_data[i].value) + 1, blob_size);
        // 3. if equal string
        TEST_ASSERT_EQUAL_STRING(blob_data[i].value, ptr);
        free(ptr);

    }
    
}
// delete all -- should work
TEST_CASE("Delete should work", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(u8_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_delete_key(ns, u8_data[i].key));
    }
    for (size_t i = 0; i < ARRAY_SIZEOF(u32_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_delete_key(ns, u32_data[i].key));
    }
    for (size_t i = 0; i < ARRAY_SIZEOF(str_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_delete_key(ns, str_data[i].key));
    }
    for (size_t i = 0; i < ARRAY_SIZEOF(blob_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_delete_key(ns, blob_data[i].key));
    }
}

// Delete some previously deleted registers -- should FAIL
TEST_CASE("Delete should fail", tag) {
    TEST_ASSERT_EQUAL(ESP_ERR_NVS_NOT_FOUND, storage_delete_key(ns, u8_data[0].key));
    TEST_ASSERT_EQUAL(ESP_ERR_NVS_NOT_FOUND, storage_delete_key(ns, u32_data[0].key));
    TEST_ASSERT_EQUAL(ESP_ERR_NVS_NOT_FOUND, storage_delete_key(ns, str_data[0].key));
    TEST_ASSERT_EQUAL(ESP_ERR_NVS_NOT_FOUND, storage_delete_key(ns, blob_data[0].key));
}
