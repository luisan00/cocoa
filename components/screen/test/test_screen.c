#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "unity.h"

#include "screen.h"
#include "logger.h"

static const char tag[] = "[screen]";

// storage_stats
TEST_CASE("mockup test case", tag) {

    TEST_ASSERT_EQUAL_INT(0, 0);
    TEST_ASSERT_EQUAL_INT(1, 1);
    TEST_ASSERT_EQUAL_INT(2, 2);
    TEST_ASSERT_EQUAL_INT(3, 3);
}
