/**
 * @brief   Test vector 2 from @ref
 * https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-2 based on the great
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
#ifndef TEST_V2_BIP32_H
#define TEST_V2_BIP32_H

#define MAIN_VERSION_PRIVATE 0x0488ade4 /*!> Mainnet version private */
#define MAIN_VERSION_PUBLIC 0x0488b21e  /*!> Mainnet version public */

#define test_seed                                                                                  \
    "fffcf9f6f3f0edeae7e4e1dedbd8d5d2cfccc9c6c3c0bdbab7b4b1aeaba8a5a29f9c999693908d8a8784817e7b78" \
    "75726f6c696663605d5a5754514e4b484542"

/**
 * @name chain m
 * @{
 */
#define chain_m_ckd "m"
#define chain_m_fingerprint 0x00000000
#define chain_m_code "60499f801b896d83179a4374aeb7822aaeaceaa0db1f85ee3e904c4defbd9689"
#define chain_m_prv_key "4b03d6fc340455b363f51020ad3ecca4f0850280cf436c70c727923f6db46c3e"
#define chain_m_pub_key "03cbcaa9c98c877a26977d00825c956a238e8dddfbd322cce4f74b0b5bd6ace4a7"
#define chain_m_xpub                                                                               \
    "xpub661MyMwAqRbcFW31YEwpkMuc5THy2PSt5bDMsktWQcFF8syAmRUapSCGu8ED9W6oDMSgv6Zz8idoc4a6mr8BDzTJ" \
    "Y47LJhkJ8UB7WEGuduB"
#define chain_m_xprv                                                                               \
    "xprv9s21ZrQH143K31xYSDQpPDxsXRTUcvj2iNHm5NUtrGiGG5e2DtALGdso3pGz6ssrdK4PFmM8NSpSBHNqPqm55Qn3" \
    "LqFtT2emdEXVYsCzC2U"

/** @} */

/**
 * @name chain m/0
 * @{
 */
#define chain_m0_ckd "m/0"
#define chain_m0_fingerprint 0xbd16bee5
#define chain_m0_code "f0909affaa7ee7abe5dd4e100598d4dc53cd709d5a5c2cac40e7412f232f7c9c"
#define chain_m0_prv_key "abe74a98f6c7eabee0428f53798f0ab8aa1bd37873999041703c742f15ac7e1e"
#define chain_m0_pub_key "02fc9e5af0ac8d9b3cecfe2a888e2117ba3d089d8585886c9c826b6b22a98d12ea"
#define chain_m0_xprv                                                                              \
    "xprv9vHkqa6EV4sPZHYqZznhT2NPtPCjKuDKGY38FBWLvgaDx45zo9WQRUT3dKYnjwih2yJD9mkrocEZXo1ex8G81dwS" \
    "M1fwqWpWkeS3v86pgKt"
#define chain_m0_xpub                                                                              \
    "xpub69H7F5d8KSRgmmdJg2KhpAK8SR3DjMwAdkxj3ZuxV27CprR9LgpeyGmXUbC6wb7ERfvrnKZjXoUmmDznezpbZb7a" \
    "p6r1D3tgFxHmwMkQTPH"
/** @} */

/**
 * @name chain m/0/2147483647'
 * @{
 */
#define chain_m1_ckd "m/0/2147483647'"
#define chain_m1_fingerprint 0x5a61ff8e
#define chain_m1_code "be17a268474a6bb9c61e1d720cf6215e2a88c5406c4aee7b38547f585c9a37d9"
#define chain_m1_prv_key "877c779ad9687164e9c2f4f0f4ff0340814392330693ce95a58fe18fd52e6e93"
#define chain_m1_pub_key "03c01e7425647bdefa82b12d9bad5e3e6865bee0502694b94ca58b666abc0a5c3b"
#define chain_m1_xprv                                                                              \
    "xprv9wSp6B7kry3Vj9m1zSnLvN3xH8RdsPP1Mh7fAaR7aRLcQMKTR2vidYEeEg2mUCTAwCd6vnxVrcjfy2kRgVsFawNz" \
    "mjuHc2YmYRmagcEPdU9"
#define chain_m1_xpub                                                                              \
    "xpub6ASAVgeehLbnwdqV6UKMHVzgqAG8Gr6riv3Fxxpj8ksbH9ebxaEyBLZ85ySDhKiLDBrQSARLq1uNRts8RuJiHjaD" \
    "MBU4Zn9h8LZNnBC5y4a"
/** @} */

/**
 * @name chain m/0/2147483647'/1
 * @{
 */
#define chain_m2_ckd "m/0/2147483647'/1"
#define chain_m2_fingerprint 0xd8ab4937
#define chain_m2_code "f366f48f1ea9f2d1d3fe958c95ca84ea18e4c4ddb9366c336c927eb246fb38cb"
#define chain_m2_prv_key "704addf544a06e5ee4bea37098463c23613da32020d604506da8c0518e1da4b7"
#define chain_m2_pub_key "03a7d1d856deb74c508e05031f9895dab54626251b3806e16b4bd12e781a7df5b9"
#define chain_m2_xprv                                                                              \
    "xprv9zFnWC6h2cLgpmSA46vutJzBcfJ8yaJGg8cX1e5StJh45BBciYTRXSd25UEPVuesF9yog62tGAQtHjXajPPdbRCH" \
    "uWS6T8XA2ECKADdw4Ef"
#define chain_m2_xpub                                                                              \
    "xpub6DF8uhdarytz3FWdA8TvFSvvAh8dP3283MY7p2V4SeE2wyWmG5mg5EwVvmdMVCQcoNJxGoWaU9DCWh89LojfZ537" \
    "wTfunKau47EL2dhHKon"
/** @} */

/**
 * @name chain m/0/2147483647'/1/2147483646'
 * @{
 */
#define chain_m3_ckd "m/0/2147483647'/1/2147483646'"
#define chain_m3_fingerprint 0x78412e3a
#define chain_m3_code "637807030d55d01f9a0cb3a7839515d796bd07706386a6eddf06cc29a65a0e29"
#define chain_m3_prv_key "f1c7c871a54a804afe328b4c83a1c33b8e5ff48f5087273f04efa83b247d6a2d"
#define chain_m3_pub_key "02d2b36900396c9282fa14628566582f206a5dd0bcc8d5e892611806cafb0301f0"
#define chain_m3_xprv                                                                              \
    "xprvA1RpRA33e1JQ7ifknakTFpgNXPmW2YvmhqLQYMmrj4xJXXWYpDPS3xz7iAxn8L39njGVyuoseXzU6rcxFLJ8HFsT" \
    "jSyQbLYnMpCqE2VbFWc"
#define chain_m3_xpub                                                                              \
    "xpub6ERApfZwUNrhLCkDtcHTcxd75RbzS1ed54G1LkBUHQVHQKqhMkhgbmJbZRkrgZw4koxb5JaHWkY4ALHY2grBGRja" \
    "DMzQLcgJvLJuZZvRcEL"
/** @} */

/**
 * @name chain m/0/2147483647'/1/2147483646'/2
 * @{
 */
#define chain_m4_ckd "m/0/2147483647'/1/2147483646'/2"
#define chain_m4_fingerprint 0x31a507b8
#define chain_m4_code "9452b549be8cea3ecb7a84bec10dcfd94afe4d129ebfd3b3cb58eedf394ed271"
#define chain_m4_prv_key "bb7d39bdb83ecf58f2fd82b6d918341cbef428661ef01ab97c28a4842125ac23"
#define chain_m4_pub_key "024d902e1a2fc7a8755ab5b694c575fce742c48d9ff192e63df5193e4c7afe1f9c"
#define chain_m4_xprv                                                                              \
    "xprvA2nrNbFZABcdryreWet9Ea4LvTJcGsqrMzxHx98MMrotbir7yrKCEXw7nadnHM8Dq38EGfSh6dqA9QWTyefMLEcB" \
    "YJUuekgW4BYPJcr9E7j"
#define chain_m4_xpub                                                                              \
    "xpub6FnCn6nSzZAw5Tw7cgR9bi15UV96gLZhjDstkXXxvCLsUXBGXPdSnLFbdpq8p9HmGsApME5hQTZ3emM2rnY5agb9" \
    "rXpVGyy3bdW6EEgAtqt"
/** @} */
#endif
/** @} */