#include "string.h"
#include "esp_log.h"
#include "unity.h"
#include "helpers.h"

static const char tag[] = "[helpers]";

// single uint8_t from string
TEST_CASE("single uint8_t from string", tag)
{
    TEST_ASSERT_EQUAL_UINT8(from_char("ca"), 0xca);
    TEST_ASSERT_EQUAL_UINT8(from_char("fe"), 0xfe);
}

// to uint8_t array from string
// similar to: to bytes, bytearray
// similar to: from_hex, hexstring, bytes_as_string, etc
TEST_CASE("to uint8_t array from string", tag)
{   ESP_LOGI(tag, "testing...\n");
    const char *hexstr = "0000cafe0000beef0000feed0000";
    const uint8_t expected[] = {0x00, 0x00, 0xca, 0xfe, 0x00, 0x00, 0xbe, 0xef, 0x00, 0x00, 0xfe, 0xed, 0x00, 0x00};
    const uint8_t *result = from_char_array(hexstr, strlen(hexstr) / 2);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, result, sizeof(result));
}

// to string from uint8_t array
TEST_CASE("to string from uint8_t array", tag)
{
    uint8_t in[] = {0x00, 0x00, 0xca, 0xfe, 0x00, 0x00, 0xbe, 0xef, 0x00, 0x00, 0xfe, 0xed, 0x00, 0x00};
    char expected[] = "0000cafe0000beef0000feed0000";
    char result[ARRAY_SIZEOF(in) * 2 + 1];
    from_u8_array(in, sizeof(in), result, ARRAY_SIZEOF(in) * 2 + 1);
    TEST_ASSERT_EQUAL_STRING(expected, result);
}
// slice n bytes of u8 array starting from pos
TEST_CASE("slice elements from u8 array", tag)
{
    uint8_t in[] = {0x00, 0x00, 0xca, 0xfe, 0x00, 0x00, 0xbe, 0xef, 0x00, 0x00, 0xfe, 0xed, 0x00, 0x00};
    uint8_t expected[] = {0xca, 0xfe};
    uint8_t *result = slice_u8(in, 2, 2);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, result, ARRAY_SIZEOF(expected));
}

// flip bytes
TEST_CASE("flip uint8_t array", tag)
{
    uint8_t in[] = {0x00, 0x00, 0xca, 0xfe, 0x00, 0x00, 0xbe, 0xef, 0x00, 0x00, 0xfe, 0xed, 0x00, 0x00};
    uint8_t expected[] = {0x00, 0x00, 0xed, 0xfe, 0x00, 0x00, 0xef, 0xbe, 0x00, 0x00, 0xfe, 0xca, 0x00, 0x00};
    uint8_t *result = flip_u8(in, sizeof(in));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, result, ARRAY_SIZEOF(expected));
}

// fromhex
TEST_CASE("fromhex", tag)
{
    const char hexstr[] = "0000cafe0000beef0000feed0000";
    const uint8_t expected[] = {0x00, 0x00, 0xca, 0xfe, 0x00, 0x00, 0xbe, 0xef, 0x00, 0x00, 0xfe, 0xed, 0x00, 0x00};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, fromhex(hexstr), ARRAY_SIZEOF(expected));
}

// tohex
TEST_CASE("fromhex", tag)
{
    uint8_t in[] = {0x00, 0x00, 0xca, 0xfe, 0x00, 0x00, 0xbe, 0xef, 0x00, 0x00, 0xfe, 0xed, 0x00, 0x00};
    const char expected[] = "0000cafe0000beef0000feed0000";

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, tohex(in, ARRAY_SIZEOF(in)), ARRAY_SIZEOF(expected));
}

// compare - equal - u8
TEST_CASE("compare two uint8_t, both equal", tag)
{
    const uint8_t expected[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};
    for (int i = 0; i < 10; i++)
    {
        uint8_t result = (uint8_t)i;
        if (equal_u8(expected[i], result) != true)
        {
            TEST_FAIL();
        }
    }
}
// compare - NOT equal - u8
TEST_CASE("compare two uint8_t, both NOT equal", tag)
{
    const uint8_t expected[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};

    for (int i = 10; i < 20; i++)
    {
        uint8_t result = (uint8_t)i;
        if (equal_u8(expected[i - 10], result) == true)
        {
            TEST_FAIL();
        }
    }
}
// compare - equal - u8 array
TEST_CASE("compare two uint8_t array", tag)
{
    const uint8_t expect[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};
    const uint8_t result[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};

    if (equal_u8_array(expect, result, ARRAY_SIZEOF(expect)) != true)
    {
        TEST_FAIL();
    }
}

// compare - equal - char
TEST_CASE("compare two char, both equal", tag)
{
    char expect[] = "0123456789abcdef";
    char result[] = "0123456789abcdef";

    for (int i = 0; i < strlen(expect); i++)
    {
        if (equal_char(expect[i], result[i]) != true)
        {
            TEST_FAIL();
        }
    }
}

// compare - not equal - char
TEST_CASE("compare two char, both NOT equal", tag)
{
    char expect[] = "fedcba9876543210";
    char result[] = "0123456789abcdef";

    for (int i = 0; i < strlen(expect); i++)
    {
        if (equal_char(expect[i], result[i]) == true)
        {
            TEST_FAIL();
        }
    }
}

// compare - equal - char -array
TEST_CASE("compare two char array", tag)
{
    char expect[] = "fedcba9876543210";
    char result[] = "0123456789abcdef";
    
    if (equal_char_array(expect, result, strlen(expect)) == true)
    {
        TEST_FAIL();
    }
}