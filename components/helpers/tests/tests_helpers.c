#include "unity.h"
#include "helpers.h"

// #include "esp_log.h"

TEST_CASE("from char to hexadecimal", "helpers")
{
    char ch = '0';
    uint8_t expected = 0x00;
    
    if (hex('a') != expected)
    {
        TEST_FAIL();
    }
}