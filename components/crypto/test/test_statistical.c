#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "logger.h"
#include "unity.h"
#include "helpers.h"

#include "statistical.h"

static const char tag[] = "[stat]";
// tests cases are examples from:
// https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf

// section 2.2.4
TEST_CASE("gamma_q 2.2.4", tag) {
    double expected = 0.801252;
    double a = 3.0 / 2.0;
    double x = 1.0 / 2.0;
    // transforming to int to avoid headache of double
    TEST_ASSERT_EQUAL_INT(1000000 * expected, 1000000 * finite_half_gamma_q(a, x));
}

// section 2.4.4
TEST_CASE("gamma_q 2.4.4", tag) {
    double expected = 0.180598;
    double a = 3.0 / 2.0;
    double x = 4.882605 / 2.0;
    TEST_ASSERT_EQUAL_INT(1000000 * expected, 1000000 * finite_half_gamma_q(a, x));
}

// section 2.5.4 / FAIL
TEST_CASE("gamma_q 2.5.4", tag) {
    double expected = 0.532069;
    double a = 1.0;
    double x = 1.2619656;
    TEST_ASSERT_EQUAL_INT(1000000 * expected, 1000000 * finite_half_gamma_q(a, x));
}

// section 2.7.4
TEST_CASE("gamma_q 2.7.4", tag) {
    double expected = 0.344154;
    double a = 2.0 / 2.0;
    double x = 2.133333 / 2.0;
    TEST_ASSERT_EQUAL_INT(1000000 * expected, 1000000 * finite_half_gamma_q(a, x));
}

// sec 2.8.4
TEST_CASE("gamma_q 2.8.4", tag) {
    double expected = 0.274932;
    double a = 5.0 / 2.0;
    double x = 3.167729 / 2.0;
    TEST_ASSERT_EQUAL_INT(1000000 * expected, 1000000 * finite_half_gamma_q(a, x));
}

// sec 2.11.4
TEST_CASE("gamma_q 2.11.4", tag) {
    double expected = 0.9057;
    double a = 2.0;
    double x = 1.6 / 2.0;
    TEST_ASSERT_EQUAL_INT(10000 * expected, 10000 * finite_half_gamma_q(a, x));
}
