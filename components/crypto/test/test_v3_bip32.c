#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "esp_log.h"
#include "unity.h"

#include "bip32.h"
#include "curves.h"
#include "memzero.h"

#include "helpers.h"
#include "test_v3_bip32.h"

static const char tag[] = "[crypto][bip32]";

static void TEST_LOGE(const char *msg, const char *_e, const char *_r) {
    ESP_LOGE(tag, "%-55s \x1b[48:5:8m%-10s\x1b[0m\nexpected:\t%s\nresult:\t\t%s\n", msg, "fail", _e,
             _r);
    TEST_FAIL();
}

static void TEST_LOGI(const char *msg) {
    ESP_LOGI(tag, "%-55s \x1b[48:5:31m%-10s\x1b[0m", msg, "successful");
}

TEST_CASE("Test vector 3", tag) {
    char str[XPUB_MAXLEN];
    uint32_t fingerprint;
    HDNode node, node2, node3;

    // Init m from seed
    int res = hdnode_from_seed(fromhex(test_seed), 64, SECP256K1_NAME, &node);
    if (res != true) {
        TEST_LOGE("Init m node from seed", test_seed, "error");
    }
    TEST_LOGI("Init m node from seed");

    ESP_LOGI(tag, "----- [chain %s] -----", chain_m_ckd);

    // fingerprint for master is always equal to zero (0)
    fingerprint = chain_m_fingerprint;
    if (fingerprint != 0x00000000) {
        TEST_LOGE("Compare fingerprint", "0", "not equal");
    }
    TEST_LOGI("Compare fingerprint");

    // fill_public key
    res = hdnode_fill_public_key(&node);
    if (res != 0) // 0 = no errors
    {
        TEST_LOGE("Fill public key", "no error", "error");
    }
    TEST_LOGI("Fill public key");

    // serialize xprv
    hdnode_serialize_private(&node, fingerprint, MAIN_VERSION_PRIVATE, str, sizeof(str));

    // compare serialized xprv
    res = equal_char_array(chain_m_xprv, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xprv", chain_m_xprv, str);
    }
    TEST_LOGI("Serialize xprv");

    // deserialize xprv
    res = hdnode_deserialize_private(chain_m_xprv, MAIN_VERSION_PRIVATE, SECP256K1_NAME, &node2,
                                     NULL);
    if (res != 0) // 0 = no errors
    {
        TEST_LOGE("Deserialize xprv", chain_m_xprv, "error");
    }
    TEST_LOGI("Deserialize xprv");

    // fill public on node2
    res = hdnode_fill_public_key(&node2);
    if (res != 0) {
        TEST_LOGE("filling [node2] public key ", "no error", "error");
    }

    TEST_ASSERT_EQUAL_MEMORY(&node, &node2, sizeof(HDNode));

    // Serialize xpub
    hdnode_serialize_public(&node, fingerprint, MAIN_VERSION_PUBLIC, str, sizeof(str));
    res = equal_char_array(chain_m_xpub, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xpub", chain_m_xpub, str);
    }
    TEST_LOGI("Serialize xpub");

    // deserialize xpub
    res =
        hdnode_deserialize_public(chain_m_xpub, MAIN_VERSION_PUBLIC, SECP256K1_NAME, &node2, NULL);
    if (res != 0) {
        TEST_LOGE("Deserialize xpub", "no error", "error");
    }
    TEST_LOGI("Deserialize xpub");

    memcpy(&node3, &node, sizeof(HDNode));
    memzero(&node3.private_key, 32);

    // [chain m/0']
    ESP_LOGI(tag, "----- [chain %s] -----", chain_m0_ckd);

    fingerprint = hdnode_fingerprint(&node);

    res = hdnode_private_ckd_prime(&node, 0);

    if (res != 1) {
        TEST_LOGE("ckd prime", "error", "not error");
    }
    TEST_LOGI("ckd prime");

    // fill public key
    res = hdnode_fill_public_key(&node);

    if (res != 0) {
        TEST_LOGE("Fill public key", "no error", "error");
    }
    TEST_LOGI("Fill public key");

    // serialize xprv
    hdnode_serialize_private(&node, fingerprint, MAIN_VERSION_PRIVATE, str, sizeof(str));
    res = equal_char_array(chain_m0_xprv, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xprv", chain_m0_xprv, str);
    }
    TEST_LOGI("Serialize xprv");

    // deserialize xprv
    res = hdnode_deserialize_private(str, MAIN_VERSION_PRIVATE, SECP256K1_NAME, &node2, NULL);
    if (res != 0) // 0 means no error
    {
        TEST_LOGE("Deserialize xprv", str, "error");
    }
    TEST_LOGI("Deserialize xprv");

    // serialize xpub
    hdnode_serialize_public(&node, fingerprint, MAIN_VERSION_PUBLIC, str, sizeof(str));

    // compare xpub
    res = equal_char_array(chain_m0_xpub, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xpub", str, "error");
    }
    TEST_LOGI("Serialize xpub");

    // deserialize xpub
    res =
        hdnode_deserialize_public(chain_m0_xpub, MAIN_VERSION_PUBLIC, SECP256K1_NAME, &node2, NULL);
    if (res != 0) {
        TEST_LOGE("Deserialize xpub", "no error", "error");
    }
    TEST_LOGI("Deserialize xpub");
}
