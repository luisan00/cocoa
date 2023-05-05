#include "esp_log.h"
#include "unity.h"
#include "bip39.h"
#include "bip32.h"
#include "curves.h"
#include "helpers.h"

static const char tag[] = "[crypto]";

uint8_t seed[64];
HDNode hdnode;

void progress_cb(uint32_t current, uint32_t total)
{
    ESP_LOGI(tag, "current %d of %d", current, total);
}

// bip39
TEST_CASE("mnemonic_generate", tag)
{
    const char *mnemonic = mnemonic_generate(256);
    TEST_ASSERT_EQUAL(true, mnemonic_check(mnemonic));
}

TEST_CASE("hdnode_from_seed", tag)
{

    const char *mnemonic = mnemonic_generate(256);
    const char *password = "test_password";

    mnemonic_to_seed(mnemonic, password, seed, progress_cb);
    hdnode_from_seed(seed, ARRAY_SIZEOF(seed), SECP256K1_NAME, &hdnode);

    int fp =  hdnode_fill_public_key(&hdnode);

    ESP_LOGI(tag, "------------------------------------------------");
    ESP_LOGI(tag, "depth: %d", hdnode.depth);
    ESP_LOGI(tag, "child_num: %d", hdnode.child_num);
    ESP_LOGI(tag, "fp: %d", fp);


}