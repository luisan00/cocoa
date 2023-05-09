idf_component_register(
    SRC_DIRS "."
    INCLUDE_DIRS "include"
    REQUIRES cmock crypto helpers)
    # next test:
    # https://github.com/trezor/trezor-firmware/blob/4175b817e1442984949216610dde70ffacce5545/crypto/tests/test_check_segwit.h#LL233C1-L234C1