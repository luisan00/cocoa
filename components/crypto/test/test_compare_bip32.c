#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "esp_log.h"
#include "unity.h"

#include "bip32.h"
#include "curves.h"

#include "helpers.h"
#include "test_compare_bip32.h"

static const char tag[] = "[crypto][bip32][compare-bip32]";

static void TEST_LOGE(const char *msg, const char *_e, const char *_r)
{
    ESP_LOGE(tag, "%-55s \x1b[48:5:8m%-10s\x1b[0m\nexpected:\t%s\nresult:\t\t%s\n", msg, "fail", _e, _r);
    TEST_FAIL();
}

static void TEST_LOGI(const char *msg)
{
    ESP_LOGI(tag, "%-55s \x1b[48:5:31m%-10s\x1b[0m", msg, "successful");
}

TEST_CASE("Test compare bip32", tag)
{
    int res;
    char msg[32];
    HDNode node1, node2, node3;

    hdnode_from_seed(fromhex(test_seed), 64, SECP256K1_NAME, &node1);
    hdnode_from_seed(fromhex(test_seed), 64, SECP256K1_NAME, &node2);

    res = hdnode_fill_public_key(&node2);
    if (res != 0)
    {
        TEST_LOGE("Fill public key", "no error", "error");
    }
    TEST_LOGI("Fill public key");

    for (int i = 0; i < 100; i++)
    {
        memcpy(&node3, &node1, sizeof(HDNode));

        // fill public key node3
        res = hdnode_fill_public_key(&node3);
        TEST_ASSERT_EQUAL(res, 0);

        // n1 private ckd
        res = hdnode_private_ckd(&node1, i);
        TEST_ASSERT_EQUAL(res, 1);

        // n2 public ckd
        res = hdnode_public_ckd(&node2, i);
        TEST_ASSERT_EQUAL(res, 1);

        // n3 public ckd
        res = hdnode_public_ckd(&node3, i);
        TEST_ASSERT_EQUAL(res, 1);

        // depth should be the same for all nodes
        TEST_ASSERT_EQUAL(node1.depth, node2.depth);
        TEST_ASSERT_EQUAL(node1.depth, node3.depth);

        // child_num should be the same for all nodes
        TEST_ASSERT_EQUAL(node1.child_num, node2.child_num);
        TEST_ASSERT_EQUAL(node1.child_num, node3.child_num);

        // chain code should be the same for all nodes
        TEST_ASSERT_EQUAL_MEMORY(node1.chain_code, node2.chain_code, 32);
        TEST_ASSERT_EQUAL_MEMORY(node1.chain_code, node3.chain_code, 32);
        
        // private key should be equal to [prv_key_zeroes] on nodes 2 and 3
        TEST_ASSERT_EQUAL_MEMORY(node2.private_key, fromhex(prv_key_zeroes), 32);
        TEST_ASSERT_EQUAL_MEMORY(node3.private_key, fromhex(prv_key_zeroes), 32);

        TEST_ASSERT_EQUAL_INT(hdnode_fill_public_key(&node1), 0);

        TEST_ASSERT_EQUAL_MEMORY(node1.public_key, node2.public_key, 33);
        TEST_ASSERT_EQUAL_MEMORY(node1.public_key, node3.public_key, 33);

        sprintf(msg, "[chain m/%d]", i);
        TEST_LOGI(msg);

    }
}
