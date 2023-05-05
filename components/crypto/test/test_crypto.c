#include <assert.h>
#include <string.h>

#include "esp_log.h"
#include "unity.h"
#include "bip39.h"
#include "bip32.h"
#include "curves.h"
#include "helpers.h"
#include "check_mem.h"

#define VERSION_PUBLIC 0x0488b21e
#define VERSION_PRIVATE 0x0488ade4

uint32_t fingerprint;
static const char tag[] = "[crypto]";
HDNode node;

void progress_cb(uint32_t current, uint32_t total)
{
    printf("%d of %d\n", current, total);
}

TEST_CASE("HDNode from seed should pass", tag)
{
    const char *seed = "000102030405060708090a0b0c0d0e0f";
    int res = hdnode_from_seed(fromhex(seed), 16, SECP256K1_NAME, &node);
    TEST_ASSERT_EQUAL(res, true);
}

TEST_CASE("compare chain code", tag)
{
    const char *chain_code = "873dff81c02f525623fd1fe5167eac3a55a049de3d314bb42ee227ffed37d508";
    TEST_ASSERT_EQUAL_UINT8_ARRAY(fromhex(chain_code), node.chain_code, 32);
}

TEST_CASE("compare private_key", tag)
{
    const char *private_key = "e8f32e723decf4051aefac8e2c93c9c5b214313817cdb01a1494b917c8436b35";
    TEST_ASSERT_EQUAL_UINT8_ARRAY(fromhex(private_key), node.private_key, 32);
}

TEST_CASE("compare public key", tag)
{
    hdnode_fill_public_key(&node);
    const char *public_key = "0339a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c2";
    TEST_ASSERT_EQUAL_UINT8_ARRAY(fromhex(public_key), node.public_key, 33);
}

TEST_CASE("serialize private key", tag)
{
    // [Chain m]
    fingerprint = 0;
    char str[XPUB_MAXLEN];
    hdnode_serialize_private(&node, fingerprint, VERSION_PRIVATE, str, sizeof(str));
    const char serialized_prv_key[] = "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi";
    TEST_ASSERT_EQUAL_STRING(serialized_prv_key, str);
}