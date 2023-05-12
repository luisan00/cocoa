
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "nvs.h"
#include "esp_timer.h"
#include "unity.h"

#include "storage.h"
#include "helpers.h"
#include "logger.h"

#include "test_storage.h"

static const char tag[] = "[storage]";

// INIT
TEST_CASE("Testing NVS init", tag)
{
    loge("quiero %d pero tengo %d", 4, 2);
    TEST_ASSERT_EQUAL(1, 1);
}
