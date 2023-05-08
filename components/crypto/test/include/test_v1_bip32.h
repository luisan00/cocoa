/**
 * @brief   Test vector 1 from @ref https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-1
 * based on the great work from @ref https://github.com/trezor/trezor-firmware/blob/master/crypto/tests/test_check.c
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
#ifndef TEST_V1_BIP32_H
#define TEST_V1_BIP32_H

#define MAIN_VERSION_PRIVATE 0x0488ade4 /*!> Mainnet version private */
#define MAIN_VERSION_PUBLIC 0x0488b21e  /*!> Mainnet version public */

#define test_seed "000102030405060708090a0b0c0d0e0f"

/**
 * @name chain m
 * @{
 */
#define chain_m_ckd "m"
#define chain_m_fingerprint 0x00000000
#define chain_m_code "873dff81c02f525623fd1fe5167eac3a55a049de3d314bb42ee227ffed37d508"
#define chain_m_prv_key "e8f32e723decf4051aefac8e2c93c9c5b214313817cdb01a1494b917c8436b35"
#define chain_m_pub_key "0339a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c2"
#define chain_m_xpub \
    "xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet8"
#define chain_m_xprv \
    "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi"

/** @} */

/**
 * @name chain m/0'
 * @{
 */
#define chain_m0_ckd "m/0'"
#define chain_m0_fingerprint 0x3442193e
#define chain_m0_code "47fdacbd0f1097043b78c63c20c34ef4ed9a111d980047ad16282c7ae6236141"
#define chain_m0_prv_key "edb2e14f9ee77d26dd93b4ecede8d16ed408ce149b6cd80b0715a2d911a0afea"
#define chain_m0_pub_key "035a784662a4a20a65bf6aab9ae98a6c068a81c52e4b032c0fb5400c706cfccc56"
#define chain_m0_xprv \
    "xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7"
#define chain_m0_xpub \
    "xpub68Gmy5EdvgibQVfPdqkBBCHxA5htiqg55crXYuXoQRKfDBFA1WEjWgP6LHhwBZeNK1VTsfTFUHCdrfp1bgwQ9xv5ski8PX9rL2dZXvgGDnw"
/** @} */

/**
 * @name chain m/0'/1
 * @{
 */
#define chain_m1_ckd "m/0'/1"
#define chain_m1_fingerprint 0x5c1bd648
#define chain_m1_code "2a7857631386ba23dacac34180dd1983734e444fdbf774041578e9b6adb37c19"
#define chain_m1_prv_key "3c6cb8d0f6a264c91ea8b5030fadaa8e538b020f0a387421a12de9319dc93368"
#define chain_m1_pub_key "03501e454bf00751f24b1b489aa925215d66af2234e3891c3b21a52bedb3cd711c"
#define chain_m1_xprv \
    "xprv9wTYmMFdV23N2TdNG573QoEsfRrWKQgWeibmLntzniatZvR9BmLnvSxqu53Kw1UmYPxLgboyZQaXwTCg8MSY3H2EU4pWcQDnRnrVA1xe8fs"
#define chain_m1_xpub \
    "xpub6ASuArnXKPbfEwhqN6e3mwBcDTgzisQN1wXN9BJcM47sSikHjJf3UFHKkNAWbWMiGj7Wf5uMash7SyYq527Hqck2AxYysAA7xmALppuCkwQ"
/** @} */

/**
 * @name chain m/0'/1/2'
 * @{
 */
#define chain_m2_ckd "m/0'/1/2'"
#define chain_m2_fingerprint 0xbef5a2f9
#define chain_m2_code "04466b9cc8e161e966409ca52986c584f07e9dc81f735db683c3ff6ec7b1503f"
#define chain_m2_prv_key "cbce0d719ecf7431d88e6a89fa1483e02e35092af60c042b1df2ff59fa424dca"
#define chain_m2_pub_key "0357bfe1e341d01c69fe5654309956cbea516822fba8a601743a012a7896ee8dc2"
#define chain_m2_xprv \
    "xprv9z4pot5VBttmtdRTWfWQmoH1taj2axGVzFqSb8C9xaxKymcFzXBDptWmT7FwuEzG3ryjH4ktypQSAewRiNMjANTtpgP4mLTj34bhnZX7UiM"
#define chain_m2_xpub \
    "xpub6D4BDPcP2GT577Vvch3R8wDkScZWzQzMMUm3PWbmWvVJrZwQY4VUNgqFJPMM3No2dFDFGTsxxpG5uJh7n7epu4trkrX7x7DogT5Uv6fcLW5"
/** @} */

/**
 * @name chain m/0'/1/2'/2
 * @{
 */
#define chain_m3_ckd "m/0'/1/2'/2"
#define chain_m3_fingerprint 0xee7ab90c
#define chain_m3_code "cfb71883f01676f587d023cc53a35bc7f88f724b1f8c2892ac1275ac822a3edd"
#define chain_m3_prv_key "0f479245fb19a38a1954c5c7c0ebab2f9bdfd96a17563ef28a6a4b1a2a764ef4"
#define chain_m3_pub_key "02e8445082a72f29b75ca48748a914df60622a609cacfce8ed0e35804560741d29"
#define chain_m3_xprv \
    "xprvA2JDeKCSNNZky6uBCviVfJSKyQ1mDYahRjijr5idH2WwLsEd4Hsb2Tyh8RfQMuPh7f7RtyzTtdrbdqqsunu5Mm3wDvUAKRHSC34sJ7in334"
#define chain_m3_xpub \
    "xpub6FHa3pjLCk84BayeJxFW2SP4XRrFd1JYnxeLeU8EqN3vDfZmbqBqaGJAyiLjTAwm6ZLRQUMv1ZACTj37sR62cfN7fe5JnJ7dh8zL4fiyLHV"
/** @} */

/**
 * @name chain m/0'/1/2'/2/1000000000
 * @{
 */
#define chain_m4_ckd "m/0'/1/2'/2/1000000000"
#define chain_m4_fingerprint 0xd880d7d8
#define chain_m4_code "c783e67b921d2beb8f6b389cc646d7263b4145701dadd2161548a8b078e65e9e"
#define chain_m4_prv_key "471b76e389e528d6de6d816857e012c5455051cad6660850e58372a6c3e6e7c8"
#define chain_m4_pub_key "022a471424da5e657499d1ff51cb43c47481a03b1e77f951fe64cec9f5a48f7011"
#define chain_m4_xprv \
    "xprvA41z7zogVVwxVSgdKUHDy1SKmdb533PjDz7J6N6mV6uS3ze1ai8FHa8kmHScGpWmj4WggLyQjgPie1rFSruoUihUZREPSL39UNdE3BBDu76"
#define chain_m4_xpub \
    "xpub6H1LXWLaKsWFhvm6RVpEL9P4KfRZSW7abD2ttkWP3SSQvnyA8FSVqNTEcYFgJS2UaFcxupHiYkro49S8yGasTvXEYBVPamhGW6cFJodrTHy"
/** @} */
#endif
/** @} */