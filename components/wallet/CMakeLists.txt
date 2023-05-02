idf_component_register(SRCS
                       "libwally/src/address.c"
                       "libwally/src/aes.c"
                       "libwally/src/anti_exfil.c"
                       "libwally/src/base58.c"
                       "libwally/src/base64.c"
                       "libwally/src/bech32.c"
                       "libwally/src/bip32.c"
                       "libwally/src/bip38.c"
                       "libwally/src/bip39.c"
                       "libwally/src/blech32.c"
                       "libwally/src/ecdh.c"
                       "libwally/src/elements.c"
                       "libwally/src/hex.c"
                       "libwally/src/hmac.c"
                       "libwally/src/internal.c"
                       "libwally/src/map.c"
                       "libwally/src/mnemonic.c"
                       "libwally/src/pbkdf2.c"
                       "libwally/src/psbt.c"
                       "libwally/src/pullpush.c"
                       "libwally/src/script.c"
                       "libwally/src/scrypt.c"
                       "libwally/src/sign.c"
                       "libwally/src/symmetric.c"
                       "libwally/src/transaction.c"
                       "libwally/src/wif.c"
                       "libwally/src/wordlist.c"
                       "libwally/src/ccan/ccan/base64/base64.c"
                       "libwally/src/ccan/ccan/crypto/ripemd160/ripemd160.c"
                       "libwally/src/ccan/ccan/crypto/sha256/sha256.c"
                       "libwally/src/ccan/ccan/crypto/sha512/sha512.c"
                       "libwally/src/ccan/ccan/str/hex/hex.c"
                       "libwally/src/secp256k1/src/secp256k1.c"
                       "libwally/src/secp256k1/src/precomputed_ecmult.c"
                       "libwally/src/secp256k1/src/precomputed_ecmult_gen.c"
                       INCLUDE_DIRS
                       "libwally/include"
                       PRIV_INCLUDE_DIRS
                       "include"
                       "libwally"
                       "libwally/src"
                       "libwally/src/ccan"
                       "libwally/src/secp256k1"
                       "libwally/src/secp256k1/src"
                       "libwally/src/secp256k1/src/modules/ecdh"
                       "libwally/src/secp256k1/src/modules/ecdsa_adaptor"
                       "libwally/src/secp256k1/src/modules/ecdsa_s2c"
                       "libwally/src/secp256k1/src/modules/extrakeys"
                       "libwally/src/secp256k1/src/modules/generator"
                       "libwally/src/secp256k1/src/modules/musig"
                       "libwally/src/secp256k1/src/modules/rangeproof"
                       "libwally/src/secp256k1/src/modules/recovery"
                       "libwally/src/secp256k1/src/modules/schnorrsig"
                       "libwally/src/secp256k1/src/modules/surjection"
                       "libwally/src/secp256k1/src/modules/whitelist"
                       REQUIRES cmock mbedtls
                       # PRIV_REQUIRES mbedtls
)

set_source_files_properties(
    libwally/src/secp256k1/src/secp256k1.c
    libwally/src/secp256k1/src/precomputed_ecmult.c
    libwally/src/secp256k1/src/precomputed_ecmult_gen.c
    libwally/src/secp256k1/src/modules/rangeproof/rangeproof_impl.h
    libwally/src/bip32.c
    libwally/src/bip38.c
    libwally/src/ccan/ccan/base64/base64.c
    libwally/src/psbt.c
    libwally/src/sign.c
    libwally/src/transaction.c
    PROPERTIES COMPILE_FLAGS
    "-Wno-nonnull-compare -Wno-unused-function -Wno-error=maybe-uninitialized -Wno-type-limits"
    )
target_compile_definitions(
    ${COMPONENT_TARGET} PUBLIC "-DHAVE_CONFIG_H"
)
target_compile_definitions(
    ${COMPONENT_TARGET} PUBLIC "-DBUILD_ELEMENTS=1"
)
target_compile_definitions(
    ${COMPONENT_TARGET} PUBLIC "-DBUILD_MINIMAL=1"
)
target_compile_definitions(
    ${COMPONENT_TARGET} PUBLIC "-DHAVE_MBEDTLS_SHA256_H"
)
target_compile_definitions(
    ${COMPONENT_TARGET} PUBLIC "-DHAVE_MBEDTLS_SHA512_H"
)

add_custom_command(
    TARGET ${COMPONENT_LIB}
    POST_BUILD COMMAND ${CMAKE_OBJCOPY} --strip-unneeded -W sha256_init -W sha256_done -W sha512_init -W sha512_done ${CMAKE_CURRENT_BINARY_DIR}/libwallet.a
)