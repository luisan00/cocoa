#include <stdio.h>
#include <string.h>
#include "unity.h"

static void print_banner(const char *text);

void app_main(void) {
    print_banner("Testing component");
    UNITY_BEGIN();
    unity_run_tests_by_tag("[bignum]", false);
    UNITY_END();
}

static void print_banner(const char *text) {
    //
    printf("\n#### %s #####\n\n", text);
}
