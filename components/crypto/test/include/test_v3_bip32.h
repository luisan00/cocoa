/**
 * @brief   Test vector 3 from @ref
 * https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-3 based on the great
 * work from @ref https://github.com/trezor/trezor-firmware/blob/master/crypto/tests/test_check.c
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
#ifndef TEST_V3_BIP32_H
#define TEST_V3_BIP32_H

#define MAIN_VERSION_PRIVATE 0x0488ade4 /*!> Mainnet version private */
#define MAIN_VERSION_PUBLIC 0x0488b21e  /*!> Mainnet version public */

#define test_seed                                                                                  \
    "4b381541583be4423346c643850da4b320e46a87ae3d2a4e6da11eba819cd4acba45d239319ac14f863b8d5ab5a0" \
    "d0c64d2e8a1e7d1457df2e5a3c51c73235be"

/**
 * @name chain m
 * @{
 */
#define chain_m_ckd "m"
#define chain_m_fingerprint 0x00000000
#define chain_m_xprv                                                                               \
    "xprv9s21ZrQH143K25QhxbucbDDuQ4naNntJRi4KUfWT7xo4EKsHt2QJDu7KXp1A3u7Bi1j8ph3EGsZ9Xvz9dGuVrtHH" \
    "s7pXeTzjuxBrCmmhgC6"
#define chain_m_xpub                                                                               \
    "xpub661MyMwAqRbcEZVB4dScxMAdx6d4nFc9nvyvH3v4gJL378CSRZiYmhRoP7mBy6gSPSCYk6SzXPTf3ND1cZAceL7S" \
    "fJ1Z3GC8vBgp2epUt13"

/** @} */

/**
 * @name chain m/0'
 * @{
 */
#define chain_m0_ckd "m/0'"
#define chain_m0_xprv                                                                              \
    "xprv9uPDJpEQgRQfDcW7BkF7eTya6RPxXeJCqCJGHuCJ4GiRVLzkTXBAJMu2qaMWPrS7AANYqdq6vcBcBUdJCVVFceUv" \
    "JFjaPdGZ2y9WACViL4L"
#define chain_m0_xpub                                                                              \
    "xpub68NZiKmJWnxxS6aaHmn81bvJeTESw724CRDs6HbuccFQN9Ku14VQrADWgqbhhTHBaohPX4CjNLf9fq9MYo6oDaPP" \
    "LPxSb7gwQN3ih19Zm4Y"
/** @} */

#endif
/** @} */