
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
// INIT
TEST_CASE("NVS init", tag) {
    //
    TEST_ASSERT_EQUAL(0, storage_init());
}
// INIT
TEST_CASE("NVS should save u8", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(u8_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_set_u8(ns, u8_data[i].key, u8_data[i].value));
    }
}
//
TEST_CASE("NVS should save u32", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(u32_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_set_u32(ns, u32_data[i].key, u32_data[i].value));
    }
}
//
TEST_CASE("NVS should save str", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(str_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_set_str(ns, str_data[i].key, str_data[i].value));
    }
}
// INIT
TEST_CASE("NVS should delete all u8 and u32 entries ", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(u8_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_delete_key(ns, u8_data[i].key));
    }

    for (size_t i = 0; i < ARRAY_SIZEOF(u32_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_delete_key(ns, u32_data[i].key));
    }
    for (size_t i = 0; i < ARRAY_SIZEOF(str_data); i++) {
        TEST_ASSERT_EQUAL(0, storage_delete_key(ns, str_data[i].key));
    }
}