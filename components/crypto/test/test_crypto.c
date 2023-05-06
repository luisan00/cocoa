#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "esp_log.h"
#include "unity.h"

#include "bip39.h"
#include "bip32.h"
#include "curves.h"
#include "memzero.h"

#include "helpers.h"

#define VERSION_PUBLIC 0x0488b21e
#define VERSION_PRIVATE 0x0488ade4

static const char tag[] = "[crypto]";

int r;
char str[XPUB_MAXLEN];
uint32_t fingerprint;
HDNode node, node1, node2, node3;

static void TEST_LOGE(const char *msg, const char *_e, const char *_r)
{
    ESP_LOGE(tag, "%-55s \x1b[48:5:8m%-10s\x1b[0m\nexpected:\t%s\nresult:\t\t%s\n", msg, "fail", _e, _r);
    TEST_FAIL();
}
static void TEST_LOGI(const char *msg)
{
    ESP_LOGI(tag, "%-55s \x1b[48:5:31m%-10s\x1b[0m", msg, "successful");
}

// _s1 is expected, _s2 is result
const char *printfmt(const char *_s1, const char *_s2)
{
    char msg_fmt[] = "%s != %s";
    static char msg[sizeof(msg_fmt) + 128 * 2];

    snprintf(msg, sizeof(msg), msg_fmt, _s1, _s2);
    return msg;
}

//
// 1246: test vector 1 from
// 1247: https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-1
//
// https://github.com/trezor/trezor-firmware/blob/master/crypto/tests/test_check.c#L1246
TEST_CASE("Test - vector_1 - [chain m]", tag)
{
    // init m
    const char seed[] = "000102030405060708090a0b0c0d0e0f";

    int res = hdnode_from_seed(fromhex(seed), 16, SECP256K1_NAME, &node);
    if (res != 1)
    {
        TEST_LOGE("HDNode (node) check from seed [chain m]", seed, "function return error");
    }
    TEST_LOGI("HDNode (node) check from seed [chain m]");

    // eq chain code
    const char chain_code[] = "873dff81c02f525623fd1fe5167eac3a55a049de3d314bb42ee227ffed37d508";
    res = equal_u8_array(fromhex(chain_code), node.chain_code, 32);
    if (res != true) // 1 = true
    {
        TEST_LOGE("HDNode (node) check chain code [chain m]", chain_code, tohex(node.chain_code, 32));
    }
    TEST_LOGI("HDNode (node) chain code [chain m]");

    // eq private key
    const char private_key_m[] = "e8f32e723decf4051aefac8e2c93c9c5b214313817cdb01a1494b917c8436b35";
    res = equal_u8_array(fromhex(private_key_m), node.private_key, 32);
    if (res != true)
    {
        TEST_LOGE("HDNode (node) private key [chain m]", private_key_m, tohex(node.private_key, 32));
    }
    TEST_LOGI("HDNode (node) private key [chain m]");

    // fill_public
    const char public_key[] = "0339a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c2";
    res = hdnode_fill_public_key(&node);
    if (res != 0) // 0 = no errors
    {
        TEST_LOGE("HDNode (node) fill public [chain m]", public_key, "function return error");
    }
    TEST_LOGI("HDNode (node) fill public [chain m]");

    // check public key
    res = equal_u8_array(fromhex(public_key), node.public_key, 33);
    if (res != true) // 1 = true
    {
        TEST_LOGE("HDNode (node) public key [chain m]", public_key, tohex(node.public_key, 33));
    }
    TEST_LOGI("HDNode (node) public key [chain m]");

    fingerprint = 0;
    // serialize private key [chain m]
    const char serialized_prv_n1[] = "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi";
    hdnode_serialize_private(&node, fingerprint, VERSION_PRIVATE, str, sizeof(str));
    res = equal_char_array(serialized_prv_n1, str, sizeof(str));
    if (res != true)
    {
        TEST_LOGE("HDNode (node) serialize private key [chain m]", serialized_prv_n1, str);
    }
    TEST_LOGI("HDNode (node) serialize private key [chain m]");

    // deserialize private key
    res = hdnode_deserialize_private(serialized_prv_n1, VERSION_PRIVATE, SECP256K1_NAME, &node2, NULL);
    if (res != 0)
    {
        TEST_LOGE("HDNode (node2) check deserialize private [chain m]", serialized_prv_n1, "function return error");
    }
    TEST_LOGI("HDNode (node2) check deserialize private [chain m]");

    // fill public
    const char serialized_public_n2[] = "xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet8";
    res = hdnode_fill_public_key(&node2);
    if (res != 0)
    {
        TEST_LOGE("HDNode (node2) check fill public [chain m]", serialized_public_n2, "function return error");
    }
    TEST_LOGI("HDNode (node2) check fill public [chain m]");

    // serialize public
    hdnode_serialize_public(&node, fingerprint, VERSION_PUBLIC, str, sizeof(str));
    res = equal_char_array(serialized_public_n2, str, sizeof(str));
    if (res != true)
    {
        TEST_LOGE("HDNode (node) check serialize public [chain m]", serialized_public_n2, str);
    }
    TEST_LOGI("HDNode (node) check serialize public [chain m]");

    // deserialize public
    res = hdnode_deserialize_public(serialized_public_n2, VERSION_PUBLIC, SECP256K1_NAME, &node2, NULL);
    if (res != 0)
    {
        TEST_LOGE("HDNode (node2) check deserialize public [chain m]", serialized_public_n2, "function return error");
    }
    TEST_LOGI("HDNode (node2) check deserialize public [chain m]");

    // copy node to node3
    memcpy(&node3, &node, sizeof(HDNode));
    memzero(&node3.private_key, 32);
    TEST_ASSERT_EQUAL_MEMORY(&node2, &node3, sizeof(HDNode));

    // [chain m/0']
    fingerprint = hdnode_fingerprint(&node);
    hdnode_private_ckd_prime(&node, 0);
    if (fingerprint != 0x3442193e) //
    {
        TEST_LOGE("HDNode (node) check fingerprint [chain m/0']", "0x3442193e", "not equal");
    }
    TEST_LOGI("HDNode (node) check fingerprint [chain m/0']");

    const char *chain_code_m0 = "47fdacbd0f1097043b78c63c20c34ef4ed9a111d980047ad16282c7ae6236141";
    // chain code equal
    res = equal_u8_array(node.chain_code, fromhex(chain_code_m0), 32);
    if (res != true)
    {
        TEST_LOGE("HDNode (node) chain code [m/0']", chain_code_m0, tohex(node.chain_code, 32));
    }
    TEST_LOGI("HDNode (node) chain code [m/0']");
    const char *private_key_m0 = "edb2e14f9ee77d26dd93b4ecede8d16ed408ce149b6cd80b0715a2d911a0afea";
    res = equal_u8_array(fromhex(private_key_m0), node.private_key, 32);
    if (res != true)
    {
        TEST_LOGE("HDNode (node) check private key [m/0']", private_key_m0, tohex(node.private_key, 32));
    }
    TEST_LOGI("HDNode (node) check private key [m/0']");

    // fill public m/0'
    res = hdnode_fill_public_key(&node);
    if (res != 0)
    {
        TEST_LOGE("HDNode (node) fill public key [m/0']", "no error", "error");
    }
    TEST_LOGI("HDNode (node) fill public key [m/0']");
    const char *public_key_m0 = "035a784662a4a20a65bf6aab9ae98a6c068a81c52e4b032c0fb5400c706cfccc56";
    res = equal_u8_array(fromhex(public_key_m0), node.public_key, 33);
    if (res != true)
    {
        TEST_LOGE("HDNode (node) check public key [m/0']", public_key_m0, tohex(node.public_key, 33));
    }
    TEST_LOGI("HDNode (node) check public key [m/0']");

    // check private m/0'
    const char serialized_private_key_m0[] = "xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7";
    hdnode_serialize_private(&node, fingerprint, VERSION_PRIVATE, str, sizeof(str));
    res = equal_char_array(serialized_private_key_m0, str, sizeof(str));
    if (res != true)
    {
        TEST_LOGE("HDNode (node) serialize private [m/0']", serialized_private_key_m0, str);
    }
    TEST_LOGI("HDNode (node) serialize private [m/0']");

    // deserialize
    res = hdnode_deserialize_private(str, VERSION_PRIVATE, SECP256K1_NAME, &node2, NULL);
    if (res != 0)
    {
        TEST_LOGE("HDNode (node2) de-serialize private [m/0']", str, "function return error");
    }
    TEST_LOGI("HDNode (node2) de-serialize private [m/0']");

    // serialize pubkey
    const char serialized_public_key_m0[] = "xpub68Gmy5EdvgibQVfPdqkBBCHxA5htiqg55crXYuXoQRKfDBFA1WEjWgP6LHhwBZeNK1VTsfTFUHCdrfp1bgwQ9xv5ski8PX9rL2dZXvgGDnw";
    hdnode_serialize_public(&node, fingerprint, VERSION_PUBLIC, str, sizeof(str));
    res = equal_char_array(serialized_public_key_m0, str, sizeof(str));
    if (res != true)
    {
        TEST_LOGE("HDNode (node) serialize public [m/0']", str, "function return error");
    }
    TEST_LOGI("HDNode (node) serialize public [m/0']");

    // deserialize public
    res = hdnode_deserialize_public(serialized_public_key_m0, VERSION_PUBLIC, SECP256K1_NAME, &node2, NULL);
    if (res != 0)
    {
        TEST_LOGE("HDNode (node2) serialize public [m/0']", "no error", "error");
    }
    // copy node to node3 and compare nodes
    memcpy(&node3, &node, sizeof(HDNode));
    memzero(&node3.private_key, 32);
    TEST_ASSERT_EQUAL_MEMORY(&node2, &node3, sizeof(HDNode));

    //  [chain m/0'/1]
    fingerprint = hdnode_fingerprint(&node);
    hdnode_private_ckd(&node, 1);
    if (fingerprint != 0x5c1bd648)
    {
        TEST_LOGE("[m/0'/1]", "0x5c1bd648", "not equal");
    }
    TEST_LOGI("HDNode (node) check fingerprint [m/0'/1]");

    // check chain code
    const char chain_code_m0_1[] = "2a7857631386ba23dacac34180dd1983734e444fdbf774041578e9b6adb37c19";
    res = equal_u8_array(fromhex(chain_code_m0_1), node.chain_code, 32);
    if (res != true)
    {
        TEST_LOGE("HDNode (node) check chain code [m/0'/1]", chain_code_m0_1, tohex(node.chain_code, 32));
    }
    TEST_LOGI("HDNode (node) check chain code [m/0'/1]");
}

// 
TEST_CASE("private key [chain m/0'/1]", tag)
{
    const char expected[] = "3c6cb8d0f6a264c91ea8b5030fadaa8e538b020f0a387421a12de9319dc93368";
    TEST_ASSERT_EQUAL_UINT8_ARRAY(fromhex(expected), node.private_key, 32);
}
