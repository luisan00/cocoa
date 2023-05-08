/**
 * @brief   Test vector 4 from @ref https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-4
 * based on the great work from @ref https://github.com/trezor/trezor-firmware/blob/master/crypto/tests/test_check.c
 *
 * mainnet versions
 *  - pub-key: 0x0488B21E
 *  - prv-key: 0x0488ADE4
 *
 * testnet versions
 *  - pub-key: 0x043587CF
 *  - prv-key: 0x04358394
 *
 * @ingroup components
 * @{
 */
#ifndef TEST_V4_BIP32_H
#define TEST_V4_BIP32_H

#define MAIN_VERSION_PRIVATE 0x0488ade4 /*!> Mainnet version private */
#define MAIN_VERSION_PUBLIC 0x0488b21e  /*!> Mainnet version public */

#define test_seed \
    "3ddd5602285899a946114506157c7997e5444528f3003f6134712147db19b678"

/**
 * @name chain m
 * @{
 */
#define chain_m_ckd "m"
#define chain_m_fingerprint 0x00000000
#define chain_m_xprv \
    "xprv9s21ZrQH143K48vGoLGRPxgo2JNkJ3J3fqkirQC2zVdk5Dgd5w14S7fRDyHH4dWNHUgkvsvNDCkvAwcSHNAQwhwgNMgZhLtQC63zxwhQmRv"
#define chain_m_xpub \
    "xpub661MyMwAqRbcGczjuMoRm6dXaLDEhW1u34gKenbeYqAix21mdUKJyuyu5F1rzYGVxyL6tmgBUAEPrEz92mBXjByMRiJdba9wpnN37RLLAXa"
/** @} */

/**
 * @name chain m/0'
 * @{
 */
#define chain_m0_ckd "m/0'"
#define chain_m0_xprv \
    "xprv9vB7xEWwNp9kh1wQRfCCQMnZUEG21LpbR9NPCNN1dwhiZkjjeGRnaALmPXCX7SgjFTiCTT6bXes17boXtjq3xLpcDjzEuGLQBM5ohqkao9G"
#define chain_m0_xpub \
    "xpub69AUMk3qDBi3uW1sXgjCmVjJ2G6WQoYSnNHyzkmdCHEhSZ4tBok37xfFEqHd2AddP56Tqp4o56AePAgCjYdvpW2PU2jbUPFKsav5ut6Ch1m"
/** @} */

/**
 * @name chain m/0'/1'
 * @{
 */
#define chain_m1_ckd "m/0'/1'"
#define chain_m1_xprv \
    "xprv9xJocDuwtYCMNAo3Zw76WENQeAS6WGXQ55RCy7tDJ8oALr4FWkuVoHJeHVAcAqiZLE7Je3vZJHxspZdFHfnBEjHqU5hG1Jaj32dVoS6XLT1"
#define chain_m1_xpub \
    "xpub6BJA1jSqiukeaesWfxe6sNK9CCGaujFFSJLomWHprUL9DePQ4JDkM5d88n49sMGJxrhpjazuXYWdMf17C9T5XnxkopaeS7jGk1GyyVziaMt"
/** @} */
#endif
/** @} */