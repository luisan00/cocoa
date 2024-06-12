#include "unity.h"
#include "bignum.h"
#include "helpers.h"
#include "logger.h"

#include "test_bignum.h"

static const char tag[] = "[crypto][bignum]";

// read_be
TEST_CASE("bignum_read_be", tag) {
    bignum256 a;
    bignum256 b = {{0x086d8bd5, 0x1018f82f, 0x11a8bb07, 0x0bc3f7af, 0x0437cd3b, 0x14087f0a,
                    0x15498fe5, 0x10b161bb, 0xc55ece}};
    bn_read_be(fromhex("c55ece858b0ddd5263f96810fe14437cd3b5e1fbd7c6a2ec1e031f05e86d8bd5"), &a);

    for (int i = 0; i < 9; i++) {
        TEST_ASSERT_EQUAL_UINT32(a.val[i], b.val[i]);
    }
}

// write_be
// test_bignum_is_equal
// test_bignum_zero
// test_bignum_is_zero
// test_bignum_one
// test_bignum_read_le
// test_bignum_write_le
// test_bignum_read_uint32
// test_bignum_write_uint32
// test_bignum_read_uint64
// test_bignum_write_uint64
// test_bignum_copy
// test_bignum_is_even
// test_bignum_is_odd
// test_bignum_is_less
// test_bignum_bitcount
// test_bignum_digitcount
// test_bignum_format_uint64
// test_bignum_format
// test_bignum_sqrt