#include <stdio.h>
#include <string.h>
#include "unity.h"

static void print_banner(const char *text);

void app_main(void)
{
    /* These are the different ways of running registered tests.
     * In practice, only one of them is usually needed.
     *
     * UNITY_BEGIN() and UNITY_END() calls tell Unity to print a summary
     * (number of tests executed/failed/ignored) of tests executed between these calls.
     */

    // unity_run_all_tests(); runs for all registerd tests
    print_banner("Running tests for helpers component");
    UNITY_BEGIN();
    unity_run_tests_by_tag("[helpers]", false);
    UNITY_END();

    print_banner("Running tests for blocks component");
    UNITY_BEGIN();
    unity_run_tests_by_tag("[blocks]", false);
    UNITY_END();

    print_banner("Running tests for screen component");
    UNITY_BEGIN();
    unity_run_tests_by_tag("[screen]", false);
    UNITY_END();
    /* This function will not return, and will be busy waiting for UART input.
     * Make sure that task watchdog is disabled if you use this function.
     */
    print_banner("Running interactive menu");

    unity_run_menu();
}

static void print_banner(const char *text)
{
    printf("\n#### %s #####\n\n", text);
}