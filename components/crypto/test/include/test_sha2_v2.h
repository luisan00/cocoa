#ifndef TEST_SHA2_V2_H
#define TEST_SHA2_V2_H
#include "sha2.h"

struct test_sha256_short
{
    int len;
    char msg[512 / 8 * 2];
    char digest[SHA256_DIGEST_LENGTH * 2 + 1];
};

struct test_sha256_short sha256_vectors_short[] = 
{
    
};


#endif // TEST_SHA2_V2_H