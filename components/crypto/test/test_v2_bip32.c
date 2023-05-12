#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "esp_log.h"
#include "unity.h"

#include "bip32.h"
#include "curves.h"
#include "memzero.h"

#include "helpers.h"
#include "test_v2_bip32 .h"

static const char tag[] = "[crypto][bip32]";

static void TEST_LOGE(const char *msg, const char *_e, const char *_r) {
    ESP_LOGE(tag, "%-55s \x1b[48:5:8m%-10s\x1b[0m\nexpected:\t%s\nresult:\t\t%s\n", msg, "fail", _e,
             _r);
    TEST_FAIL();
}

static void TEST_LOGI(const char *msg) {
    ESP_LOGI(tag, "%-55s \x1b[48:5:31m%-10s\x1b[0m", msg, "successful");
}

TEST_CASE("Test vector 2", tag) {
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

    // compare chain code
    res = equal_u8_array(fromhex(chain_m_code), node.chain_code, 32);
    if (res != true) {
        TEST_LOGE("Compare chain code", chain_m_code, tohex(node.chain_code, 32));
    }
    TEST_LOGI("Compare chain code");

    // compare private key
    res = equal_u8_array(fromhex(chain_m_prv_key), node.private_key, 32);
    if (res != true) {
        TEST_LOGE("Compare private key", chain_m_prv_key, tohex(node.private_key, 32));
    }
    TEST_LOGI("Compare private key");

    // fill_public key
    res = hdnode_fill_public_key(&node);
    if (res != 0) // 0 = no errors
    {
        TEST_LOGE("Fill public key", chain_m_pub_key, "error");
    }
    TEST_LOGI("Fill public key");

    // compare public key
    res = equal_u8_array(fromhex(chain_m_pub_key), node.public_key, 33);
    if (res != true) {
        TEST_LOGE("Compare public key", chain_m_pub_key, tohex(node.public_key, 33));
    }
    TEST_LOGI("Compare public key");

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

    // [chain m/0]
    ESP_LOGI(tag, "----- [chain %s] -----", chain_m0_ckd);

    fingerprint = hdnode_fingerprint(&node);

    hdnode_private_ckd(&node, 0);
    if (fingerprint != chain_m0_fingerprint) {
        TEST_LOGE("Compare fingerprint", "equal", "not equal");
    }
    TEST_LOGI("Compare fingerprint");

    // compare chain code
    res = equal_u8_array(node.chain_code, fromhex(chain_m0_code), 32);
    if (res != true) {
        TEST_LOGE("Compare chain code", chain_m0_code, tohex(node.chain_code, 32));
    }
    TEST_LOGI("Compare chain code");

    // compare private
    res = equal_u8_array(fromhex(chain_m0_prv_key), node.private_key, 32);
    if (res != true) {
        TEST_LOGE("Compare private key", chain_m0_prv_key, tohex(node.private_key, 32));
    }
    TEST_LOGI("Compare private key");

    // fill public key
    res = hdnode_fill_public_key(&node);

    if (res != 0) {
        TEST_LOGE("Fill public key", "no error", "error");
    }
    TEST_LOGI("Fill public key");

    // check public key
    res = equal_u8_array(fromhex(chain_m0_pub_key), node.public_key, 33);
    if (res != true) {
        TEST_LOGE("Compare public key", chain_m0_pub_key, tohex(node.public_key, 33));
    }
    TEST_LOGI("Compare public key");

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

    memcpy(&node3, &node, sizeof(HDNode));
    memzero(&node3.private_key, 32);

    // [chain m/0/2147483647']
    ESP_LOGI(tag, "----- [chain %s] -----", chain_m1_ckd);

    // compare fingerprint
    fingerprint = hdnode_fingerprint(&node);
    hdnode_private_ckd_prime(&node, 2147483647);
    if (fingerprint != chain_m1_fingerprint) {
        TEST_LOGE("Compare fingerprint", "equal", "not equal");
    }
    TEST_LOGI("Compare fingerprint");

    // compare chain code
    res = equal_u8_array(node.chain_code, fromhex(chain_m1_code), 32);
    if (res != true) {
        TEST_LOGE("Compare chain code", chain_m1_code, tohex(node.chain_code, 32));
    }
    TEST_LOGI("Compare chain code");

    // compare private
    res = equal_u8_array(fromhex(chain_m1_prv_key), node.private_key, 32);
    if (res != true) {
        TEST_LOGE("Compare private key", chain_m1_prv_key, tohex(node.private_key, 32));
    }
    TEST_LOGI("Compare private key");

    res = hdnode_fill_public_key(&node);
    if (res != 0) {
        TEST_LOGE("Fill public key", "no error", "error");
    }
    TEST_LOGI("Fill public key");

    // compare public key
    res = equal_u8_array(fromhex(chain_m1_pub_key), node.public_key, 33);
    if (res != true) {
        TEST_LOGE("Compare public key", chain_m1_pub_key, tohex(node.public_key, 33));
    }
    TEST_LOGI("Compare public key");

    // serialize xprv
    hdnode_serialize_private(&node, fingerprint, MAIN_VERSION_PRIVATE, str, sizeof(str));
    res = equal_char_array(chain_m1_xprv, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xprv", chain_m1_xprv, str);
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
    res = equal_char_array(chain_m1_xpub, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xpub", str, "error");
    }
    TEST_LOGI("Serialize xpub");

    // deserialize xpub
    res =
        hdnode_deserialize_public(chain_m1_xpub, MAIN_VERSION_PUBLIC, SECP256K1_NAME, &node2, NULL);
    if (res != 0) {
        TEST_LOGE("Deserialize xpub", "no error", "error");
    }
    TEST_LOGI("Deserialize xpub");

    memcpy(&node3, &node, sizeof(HDNode));
    memzero(&node3.private_key, 32);

    // [Chain m/0/2147483647'/1']
    ESP_LOGI(tag, "----- [chain %s] -----", chain_m2_ckd);

    // compare fingerprint
    fingerprint = hdnode_fingerprint(&node);
    hdnode_private_ckd(&node, 1);
    if (fingerprint != chain_m2_fingerprint) {
        TEST_LOGE("Compare fingerprint", "equal", "not equal");
    }
    TEST_LOGI("Compare fingerprint");

    // compare chain code
    res = equal_u8_array(node.chain_code, fromhex(chain_m2_code), 32);
    if (res != true) {
        TEST_LOGE("Compare chain code", chain_m2_code, tohex(node.chain_code, 32));
    }
    TEST_LOGI("Compare chain code");

    // compare private
    res = equal_u8_array(fromhex(chain_m2_prv_key), node.private_key, 32);
    if (res != true) {
        TEST_LOGE("Compare private key", chain_m2_prv_key, tohex(node.private_key, 32));
    }
    TEST_LOGI("Compare private key");

    res = hdnode_fill_public_key(&node);
    if (res != 0) {
        TEST_LOGE("Fill public key", "no error", "error");
    }
    TEST_LOGI("Fill public key");

    // compare public key
    res = equal_u8_array(fromhex(chain_m2_pub_key), node.public_key, 33);
    if (res != true) {
        TEST_LOGE("Compare public key", chain_m1_pub_key, tohex(node.public_key, 33));
    }
    TEST_LOGI("Compare public key");

    // serialize xprv
    hdnode_serialize_private(&node, fingerprint, MAIN_VERSION_PRIVATE, str, sizeof(str));
    res = equal_char_array(chain_m2_xprv, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xprv", chain_m2_xprv, str);
    }
    TEST_LOGI("Serialize xprv");

    // deserialize xprv
    res = hdnode_deserialize_private(str, MAIN_VERSION_PRIVATE, SECP256K1_NAME, &node2, NULL);
    if (res != 0) // 0 means no error
    {
        TEST_LOGE("Deserialize xprv", str, "error");
    }
    TEST_LOGI("Deserialize xprv");

    // serialize xpub [chain m/0'/1/2']
    hdnode_serialize_public(&node, fingerprint, MAIN_VERSION_PUBLIC, str, sizeof(str));

    // compare xpub [chain m/0'/1/2']
    res = equal_char_array(chain_m2_xpub, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xpub", str, "error");
    }
    TEST_LOGI("Serialize xpub");

    // deserialize xpub [chain m/0'/1/2']
    res =
        hdnode_deserialize_public(chain_m2_xpub, MAIN_VERSION_PUBLIC, SECP256K1_NAME, &node2, NULL);
    if (res != 0) {
        TEST_LOGE("Deserialize xpub", "no error", "error");
    }
    TEST_LOGI("Deserialize xpub");

    memcpy(&node3, &node, sizeof(HDNode));
    memzero(&node3.private_key, 32);

    // [chain m/0/2147483647'/1/2147483646']
    ESP_LOGI(tag, "----- [chain %s] -----", chain_m3_ckd);

    // compare fingerprint
    fingerprint = hdnode_fingerprint(&node);
    hdnode_private_ckd_prime(&node, 2147483646);
    if (fingerprint != chain_m3_fingerprint) {
        TEST_LOGE("Compare fingerprint", "equal", "not equal");
    }
    TEST_LOGI("Compare fingerprint");

    // compare chain code
    res = equal_u8_array(node.chain_code, fromhex(chain_m3_code), 32);
    if (res != true) {
        TEST_LOGE("Compare chain code", chain_m3_code, tohex(node.chain_code, 32));
    }
    TEST_LOGI("Compare chain code");

    // compare private
    res = equal_u8_array(fromhex(chain_m3_prv_key), node.private_key, 32);
    if (res != true) {
        TEST_LOGE("Compare private key", chain_m3_prv_key, tohex(node.private_key, 32));
    }
    TEST_LOGI("Compare private key");

    res = hdnode_fill_public_key(&node);
    if (res != 0) {
        TEST_LOGE("Fill public key", "no error", "error");
    }
    TEST_LOGI("Fill public key");

    // compare public key
    res = equal_u8_array(fromhex(chain_m3_pub_key), node.public_key, 33);
    if (res != true) {
        TEST_LOGE("Compare public key", chain_m3_pub_key, tohex(node.public_key, 33));
    }
    TEST_LOGI("Compare public key");

    // serialize xprv
    hdnode_serialize_private(&node, fingerprint, MAIN_VERSION_PRIVATE, str, sizeof(str));
    res = equal_char_array(chain_m3_xprv, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xprv", chain_m3_xprv, str);
    }
    TEST_LOGI("Serialize xprv");

    // deserialize xprv
    res = hdnode_deserialize_private(str, MAIN_VERSION_PRIVATE, SECP256K1_NAME, &node2, NULL);
    if (res != 0) // 0 means no error
    {
        TEST_LOGE("Deserialize xprv", str, "error");
    }
    TEST_LOGI("Deserialize xprv");

    // serialize xpub [chain m/0'/1/2'/2]
    hdnode_serialize_public(&node, fingerprint, MAIN_VERSION_PUBLIC, str, sizeof(str));

    // compare xpub [chain m/0'/1/2'/2]
    res = equal_char_array(chain_m3_xpub, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xpub", str, "error");
    }
    TEST_LOGI("Serialize xpub");

    // deserialize xpub [chain m/0'/1/2'/2]
    res =
        hdnode_deserialize_public(chain_m3_xpub, MAIN_VERSION_PUBLIC, SECP256K1_NAME, &node2, NULL);
    if (res != 0) {
        TEST_LOGE("Deserialize xpub", "no error", "error");
    }
    TEST_LOGI("Deserialize xpub");

    memcpy(&node3, &node, sizeof(HDNode));
    memzero(&node3.private_key, 32);

    // [Chain m/0/2147483647'/1/2147483646'/2]
    ESP_LOGI(tag, "----- [chain %s] -----", chain_m4_ckd);

    // compare fingerprint
    fingerprint = hdnode_fingerprint(&node);
    hdnode_private_ckd(&node, 2);
    if (fingerprint != chain_m4_fingerprint) {
        TEST_LOGE("Compare fingerprint", "equal", "not equal");
    }
    TEST_LOGI("Compare fingerprint");

    // compare chain code
    res = equal_u8_array(node.chain_code, fromhex(chain_m4_code), 32);
    if (res != true) {
        TEST_LOGE("Compare chain code", chain_m4_code, tohex(node.chain_code, 32));
    }
    TEST_LOGI("Compare chain code");

    // compare private
    res = equal_u8_array(fromhex(chain_m4_prv_key), node.private_key, 32);
    if (res != true) {
        TEST_LOGE("Compare private key", chain_m4_prv_key, tohex(node.private_key, 32));
    }
    TEST_LOGI("Compare private key");

    res = hdnode_fill_public_key(&node);
    if (res != 0) {
        TEST_LOGE("Fill public key", "no error", "error");
    }
    TEST_LOGI("Fill public key");

    // compare public key
    res = equal_u8_array(fromhex(chain_m4_pub_key), node.public_key, 33);
    if (res != true) {
        TEST_LOGE("Compare public key", chain_m4_pub_key, tohex(node.public_key, 33));
    }
    TEST_LOGI("Compare public key");

    // serialize xprv
    hdnode_serialize_private(&node, fingerprint, MAIN_VERSION_PRIVATE, str, sizeof(str));
    res = equal_char_array(chain_m4_xprv, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xprv", chain_m4_xprv, str);
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
    res = equal_char_array(chain_m4_xpub, str, sizeof(str));
    if (res != true) {
        TEST_LOGE("Serialize xpub", str, "error");
    }
    TEST_LOGI("Serialize xpub");

    // deserialize xpub
    res =
        hdnode_deserialize_public(chain_m4_xpub, MAIN_VERSION_PUBLIC, SECP256K1_NAME, &node2, NULL);
    if (res != 0) {
        TEST_LOGE("Deserialize xpub", "no error", "error");
    }
    TEST_LOGI("Deserialize xpub");
}
