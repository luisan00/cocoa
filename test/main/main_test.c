#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "unity.h"

static void print_banner(const char *text);

void app_main(void) {
    print_banner("Testing component");
    /*
    UNITY_BEGIN();
    unity_run_tests_by_tag("[bignum]", false);
    UNITY_END();
    */
    UNITY_BEGIN();
    unity_run_tests_by_tag("[screen]", false);
    UNITY_END();

    print_banner("Starting interactive test menu");
    /* This function will not return, and will be busy waiting for UART input.
     * Make sure that task watchdog is disabled if you use this function.
     */
    unity_run_menu();
}

static void print_banner(const char *text) {
    //
    printf("\n#### %s #####\n\n", text);
}
