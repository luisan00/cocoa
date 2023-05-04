#include "esp_log.h"
#include "unity.h"
#include "wallet.h"

static const char tag[] = "[wallet]";

TEST_CASE("wallet_err_to_name(WALLET_OK)", tag)
{
    char *expected_ok = "WALLET_OK";
    TEST_ASSERT_EQUAL_STRING(expected_ok, wallet_err_to_name(WALLET_OK));
}
TEST_CASE("wallet_err_to_name(WALLET_ERROR)", tag)
{
    char *expected_err = "WALLET_ERROR";
    TEST_ASSERT_EQUAL_STRING(expected_err, wallet_err_to_name(WALLET_ERROR));
}