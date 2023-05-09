#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "esp_timer.h"
#include "esp_log.h"
#include "unity.h"

#include "bip32.h"
#include "curves.h"
#include "memzero.h"
#include "secp256k1.h"

#include "helpers.h"
#include "test_optimized_bip32.h"

static const char tag[] = "[crypto][bip32][optimized-bip32]";

static void TEST_LOGE(const char *msg, const char *_e, const char *_r)
{
    ESP_LOGE(tag, "%-55s \x1b[48:5:8m%-10s\x1b[0m\nexpected:\t%s\nresult:\t\t%s\n", msg, "fail", _e, _r);
    TEST_FAIL();
}

static void TEST_LOGI(const char *msg)
{
    ESP_LOGI(tag, "%-55s \x1b[48:5:31m%-10s\x1b[0m", msg, "successful");
}

TEST_CASE("optimized bip32", tag)
{
    char msg[64];

    HDNode root;

    hdnode_from_seed((uint8_t *)test_seed, 16, SECP256K1_NAME, &root);

    TEST_ASSERT_EQUAL(hdnode_fill_public_key(&root), 0);

    curve_point pub;
    ecdsa_read_pubkey(&secp256k1, root.public_key, &pub);

    HDNode node;
    char addr1[MAX_ADDR_SIZE], addr2[MAX_ADDR_SIZE];

    uint64_t elapsed; // = esp_timer_get_time();

    for (int i = 0; i < 50; i++)
    {

        memcpy(&node, &root, sizeof(HDNode));

        elapsed = esp_timer_get_time();

        // unoptimized
        hdnode_public_ckd(&node, i);
        TEST_ASSERT_EQUAL(hdnode_fill_public_key(&node), 0);
        ecdsa_get_address(node.public_key, 0, HASHER_SHA2_RIPEMD, HASHER_SHA2D,
                          addr1, sizeof(addr1));

        // optimized
        hdnode_public_ckd_address_optimized(&pub, root.chain_code, i, 0,
                                            HASHER_SHA2_RIPEMD, HASHER_SHA2D, addr2,
                                            sizeof(addr2), 0);
        // count relative millis
        elapsed = esp_timer_get_time() - elapsed;

        // check if both addresses are the same
        if (equal_char_array(addr1, addr2, strlen(addr1)) != true)
        {
            // if addresses are not the same, the test will fail 
            TEST_LOGE("addr1 is not equal to addr2", addr1, addr2);
        }
        // print partial results
        sprintf(msg, "[chain m/%d] %lld ms", i, elapsed / 1000);
        TEST_LOGI(msg);
    }
}