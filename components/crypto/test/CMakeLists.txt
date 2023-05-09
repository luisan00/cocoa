idf_component_register(
    SRC_DIRS "."
    INCLUDE_DIRS "include"
    REQUIRES cmock crypto helpers)
    # next test:
    # https://github.com/trezor/trezor-firmware/blob/master/crypto/tests/test_check.c#L2009