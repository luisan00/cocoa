
#include "unity.h"
#include "logger.h"
#include "hmi.h"

static const char tag[] = "[hmi]";

static int wait_for_button(hmi_dev_t btn);
static int wait_for_btn_push(hmi_dev_t btn);
static int wait_for_btn_release(hmi_dev_t btn);

TEST_CASE("push buttons, basic (I)", tag) {

    for (size_t i = 0; i < HMI_NUMOF; i++) {
        TEST_ASSERT_EQUAL_INT(0, wait_for_button(hmi_dev[i]));
    }
}

static int wait_for_button(hmi_dev_t btn) {
    int res;
    res = wait_for_btn_push(btn);
    res = wait_for_btn_release(btn);
    return res;
}

static int wait_for_btn_push(hmi_dev_t btn) {
    int res = 1;
    logi("Push down %s and hold it down", btn.name);
    do {
        int r = btn_read(btn);
        if (!r) {
            res = 0;
        }
    } while (res);
    return res;
}

static int wait_for_btn_release(hmi_dev_t btn) {
    int res = 1;
    logi("Release %s", btn.name);
    do {
        int r = btn_read(btn);
        if (r) {
            res = 0;
        }
    } while (res);
    return res;
}