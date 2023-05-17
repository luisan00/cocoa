/**
 * Copyright (c) 2023 luisan00 <luisan00@hotmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @brief       Tests for gamma component
 * @author      luisan00 <luisan00@hotmail.com>
 */
#include <stdint.h>
#include "esp_log.h"
#include "unity.h"
#include "logger.h"
#include "cephes.h"

static const char tag[] = "[cephes]";

// section 2.2.4 -- PASS
TEST_CASE("gamma_q 2.2.4", tag) {
    float expected = 0.801252;
    double a = 3.0 / 2.0;
    double x = 1.0 / 2.0;
    float result = (float)cephes_igamc(a, x);
    logi("expected: %f result: %f", expected, result);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// section 2.4.4 -- PASS
TEST_CASE("gamma_q 2.4.4", tag) {
    float expected = 0.180598;
    double a = 3.0 / 2.0;
    double x = 4.882605 / 2.0;
    float result = (float)cephes_igamc(a, x);
    logi("expected: %f result: %f", expected, result);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// section 2.5.4 -- FAIL
TEST_CASE("gamma_q 2.5.4", tag) {
    float expected = 0.532069;
    double a = 1.0;
    double x = 1.2619656;
    float result = (float)cephes_igamc(a, x);
    logi("expected: %f result: %f", expected, result);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// section 2.7.4 -- PASS
TEST_CASE("gamma_q 2.7.4", tag) {
    float expected = 0.344154;
    double a = 2.0 / 2.0;
    double x = 2.133333 / 2.0;
    float result = (float)cephes_igamc(a, x);
    logi("expected: %f result: %f", expected, result);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// sec 2.8.4 -- FAIL
TEST_CASE("gamma_q 2.8.4", tag) {
    float expected = 0.274932;
    double a = 5.0 / 2.0;
    double x = 3.167729 / 2.0;
    float result = (float)cephes_igamc(a, x);
    logi("expected: %f result: %f", expected, result);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}

// sec 2.11.4 -- FAIL
TEST_CASE("gamma_q 2.11.4", tag) {
    float expected = 0.9057;
    double a = 2.0;
    double x = 1.6 / 2.0;
    float result = (float)cephes_igamc(a, x);
    logi("expected: %f result: %f", expected, result);
    TEST_ASSERT_EQUAL_FLOAT(expected, result);
}
