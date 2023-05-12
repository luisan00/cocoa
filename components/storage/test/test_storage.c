
#include "esp_log.h"
#include "nvs.h"
#include "unity.h"

#include "storage.h"

#include "helpers.h"
#include "test_storage.h"

static const char tag[] = "[storage]";
static const char namespace[] = "test";

TEST_CASE("Testing NVS init", tag)
{
    TEST_ASSERT_EQUAL(nvs_init(), ESP_OK);
}

TEST_CASE("Testing SAVE uint8_t", tag)
{
    for (size_t i = 0; i < ARRAY_SIZEOF(kv_u8); i++)
    {
        TEST_ASSERT_EQUAL_INT(nvs_set_uint8(namespace, kv_u8[i].key, kv_u8[i].value), ESP_OK);
    }
}

TEST_CASE("Testing GET uint8_t", tag)
{
    for (size_t i = 0; i < ARRAY_SIZEOF(kv_u8); i++)
    {
        uint8_t __u8_value;

        if (nvs_get_uint8(namespace, kv_u8[i].key, &__u8_value) != ESP_OK)
        {
            TEST_FAIL();
        }
        TEST_ASSERT_EQUAL_UINT8(__u8_value, kv_u8[i].value);
    }
}

TEST_CASE("It should return ESP_OK: SAVE uint32_t", tag)
{
    for (size_t i = 0; i < ARRAY_SIZEOF(kv_u32); i++)
    {

        TEST_ASSERT_EQUAL_INT(nvs_set_uint32(namespace, kv_u32[i].key, kv_u32[i].value), ESP_OK);
    }
}

TEST_CASE("It should return ESP_OK: GET uint32_t", tag)
{
    for (size_t i = 0; i < ARRAY_SIZEOF(kv_u8); i++)
    {
        uint32_t __u32_value;

        if (nvs_get_uint32(namespace, kv_u32[i].key, &__u32_value) != ESP_OK)
        {
            TEST_FAIL();
        }
        TEST_ASSERT_EQUAL_UINT8(__u32_value, kv_u8[i].value);
    }
}

TEST_CASE("It should return ESP_OK: delete u8 key", tag)
{
    // delete an element of kv_u8
    TEST_ASSERT_EQUAL_INT(nvs_delete_key(namespace, kv_u8[0].key), ESP_OK);
}

TEST_CASE("It should return ESP_OK: delete u32 key", tag)
{
    // delelete an element of kv_u32
    TEST_ASSERT_EQUAL_INT(nvs_delete_key(namespace, kv_u32[0].key), ESP_OK);
}

TEST_CASE("It should return ESP_ERR_NVS_NOT_FOUND: delete u8 key", tag)
{
    // trying again to delete an entry of kv_u8
    TEST_ASSERT_EQUAL_INT(nvs_delete_key(namespace, kv_u8[0].key), ESP_ERR_NVS_NOT_FOUND);
}

TEST_CASE("It should return ESP_ERR_NVS_NOT_FOUND: delete u32 key", tag)
{
    // trying again to delete an entry of kv_u32
    TEST_ASSERT_EQUAL_INT(nvs_delete_key(namespace, kv_u32[0].key), ESP_ERR_NVS_NOT_FOUND);
}

/*
TEST_CASE("Testing deinit default nvs partition", tag)
{
    TEST_ASSERT_EQUAL_INT(nvs_deinit(), ESP_OK);
}
*/