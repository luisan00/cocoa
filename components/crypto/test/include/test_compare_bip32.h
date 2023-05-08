/**
 * @brief   Test compare is based on the great work from:
 *  @ref https://github.com/trezor/trezor-firmware/blob/master/crypto/tests/test_check.c
 *
 * mainnet versions
 *  - pub-key: 0x0488B21E
 *  - prv-key: 0x0488ADE4
 *
 * testnet versions
 *  - pub-key: 0x043587CF
 *  - prv-key: 0x04358394
 * @{
 */
#ifndef TEST_COMPARE_BIP32_H
#define TEST_COMPARE_BIP32_H

#define MAIN_VERSION_PRIVATE 0x0488ade4 /*!> Mainnet version private */
#define MAIN_VERSION_PUBLIC 0x0488b21e  /*!> Mainnet version public */

#define test_seed "301133282ad079cbeb59bc446ad39d333928f74c46997d3609cd3e2801ca69d62788"
#define prv_key_zeroes "0000000000000000000000000000000000000000000000000000000000000000"
#endif
/** @} */