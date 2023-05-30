#include "unity.h"
#include "sha2.h"
#include "sha3.h"
#include "helpers.h"
#include "logger.h"
#include "test_sha.h"

static const char tag[] = "[crypto][sha]";

// sha256 test
TEST_CASE("sha256", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(sha256_data); i++) {
        printf("sha256: Computing %d of %d\n", i + 1, ARRAY_SIZEOF(sha256_data));
        SHA256_CTX ctx;
        uint8_t digest[SHA256_DIGEST_LENGTH];
        sha256_Init(&ctx);
        /* extra bits are not supported */
        if (sha256_data[i].numberExtrabits) {
            continue;
        }
        for (int j = 0; j < sha256_data[i].repeatcount; j++) {
            sha256_Update(&ctx, (const uint8_t *)sha256_data[i].test, sha256_data[i].length);
        }
        sha256_Final(&ctx, digest);
        TEST_ASSERT_EQUAL_UINT8_ARRAY(fromhex(sha256_data[i].result), digest, SHA256_DIGEST_LENGTH);
    }
}

// sha512 test
TEST_CASE("sha512", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(sha512_data); i++) {
        printf("sha512: Computing %d of %d\n", i + 1, ARRAY_SIZEOF(sha512_data));
        SHA512_CTX ctx;
        uint8_t digest[SHA512_DIGEST_LENGTH];
        sha512_Init(&ctx);
        /* extra bits are not supported */
        if (sha512_data[i].numberExtrabits) {
            continue;
        }
        for (int j = 0; j < sha512_data[i].repeatcount; j++) {
            sha512_Update(&ctx, (const uint8_t *)sha512_data[i].test, sha512_data[i].length);
        }
        sha512_Final(&ctx, digest);
        TEST_ASSERT_EQUAL_UINT8_ARRAY(fromhex(sha512_data[i].result), digest, SHA512_DIGEST_LENGTH);
    }
}

// sha3-256 test
TEST_CASE("sha3_256", tag) {
    for (size_t i = 0; i < ARRAY_SIZEOF(sha3_256_data); i++) {
        printf("sha3-256: Computing %d of %d\n", i + 1, ARRAY_SIZEOF(sha3_256_data));

        uint8_t digest[SHA3_256_DIGEST_LENGTH];
        size_t len = strlen(sha3_256_data[i].test);
        sha3_256((uint8_t *)sha3_256_data[i].test, len, digest);
        // ck_assert_mem_eq(digest, fromhex(tests[i].hash), SHA3_256_DIGEST_LENGTH);

        // Test progressive hashing.
        size_t part_len = len;
        SHA3_CTX ctx;
        sha3_256_Init(&ctx);
        sha3_Update(&ctx, (uint8_t *)sha3_256_data[i].test, part_len);
        sha3_Update(&ctx, NULL, 0);
        sha3_Update(&ctx, (uint8_t *)sha3_256_data[i].test + part_len, len - part_len);
        sha3_Final(&ctx, digest);
        TEST_ASSERT_EQUAL_UINT8_ARRAY(fromhex(sha3_256_data[i].result), digest,
                                      SHA3_256_DIGEST_LENGTH);
    }
}

// sha3-512 test
TEST_CASE("sha3_512", tag) {

    for (size_t i = 0; i < ARRAY_SIZEOF(sha3_512_data); i++) {
        printf("sha3-512: Computing %d of %d\n", i + 1, ARRAY_SIZEOF(sha3_512_data));

        uint8_t digest[SHA3_512_DIGEST_LENGTH];
        size_t len = strlen(sha3_512_data[i].test);
        sha3_512((uint8_t *)sha3_512_data[i].test, len, digest);

        // Test progressive hashing.
        size_t part_len = len;
        SHA3_CTX ctx;
        sha3_512_Init(&ctx);
        sha3_Update(&ctx, (const uint8_t *)sha3_512_data[i].test, part_len);
        sha3_Update(&ctx, NULL, 0);
        sha3_Update(&ctx, (const uint8_t *)sha3_512_data[i].test + part_len, len - part_len);
        sha3_Final(&ctx, digest);
        TEST_ASSERT_EQUAL_UINT8_ARRAY(fromhex(sha3_512_data[i].result), digest,
                                      SHA3_512_DIGEST_LENGTH);
    }
}