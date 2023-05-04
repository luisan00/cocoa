#include "esp_log.h"
#include "unity.h"
#include "bip39.h"

static const char tag[] = "[crypto]";

TEST_CASE("-- mocked -- [crypto] -- component --", tag)
{
    TEST_ASSERT_EQUAL(BIP39_WORD_COUNT, 2048);
}

TEST_CASE("mnemonic generate", tag){
    ESP_LOGI(tag, "mnemonic: %s",  mnemonic_generate(200));
}