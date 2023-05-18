idf_component_register(
    SRCS 
        # sub-component address
        "address/address.c"
        # sub-component base58
        "base58/base58.c"
        # sub-component bignum
        "bignum/bignum.c"
        # sub-component bip32
        "bip32/bip32.c"
        # sub-component bip39
        "bip39/bip39.c"
        "bip39/bip39_english.c"
        # sub-component blake2
        "blake2/blake2b.c"
        "blake2/blake2s.c"
        "blake2/blake256.c"
        # sub-component cardano
        "cardano/cardano.c"
        # sub-component check-mem
        "check_mem/check_mem.c"
        # sub-component curves
        "curves/curves.c"
        # sub-component ecdsa
        "ecdsa/ecdsa.c"
        # sub-component ed25519-donna
        "ed25519-donna/curve25519-donna-32bit.c"
        "ed25519-donna/curve25519-donna-helpers.c"
        "ed25519-donna/curve25519-donna-scalarmult-base.c"
        "ed25519-donna/ed25519-donna-32bit-tables.c"
        "ed25519-donna/ed25519-donna-basepoint-table.c"
        "ed25519-donna/ed25519-donna-impl-base.c"
        "ed25519-donna/ed25519-keccak.c"
        "ed25519-donna/ed25519-sha3.c"
        "ed25519-donna/ed25519.c"
        "ed25519-donna/modm-donna-32bit.c"
        # sub-component groestl
        "groestl/groestl.c"
        # sub-component hasher
        "hasher/hasher.c"
        # sub-compoennt hmac
        "hmac/hmac.c"
        "hmac/hmac_drbg.c"
        # sub-component memzero
        "memzero/memzero.c"
        # sub-component nist256p1
        "nist256p1/nist256p1.c"
        "nist256p1/nist256p1.table"
        # sub-component pdkdf2
        "pbkdf2/pbkdf2.c"
        # sub-component random
        "rand/rand.c"
        "rand/statistical.c"
        # sub-component rfc6979
        "rfc6979/rfc6979.c"
        # sub-component ripemd160
        "ripemd160/ripemd160.c"
        # sub-component script
        "script/script.c"
        # sub-component
        "secp256k1/secp256k1.c"
        "secp256k1/secp256k1.table"
        # subcomponent segwit_addr
        "segwit_addr/segwit_addr.c"
        # sub-component sha
        "sha/sha2.c"
        "sha/sha3.c"
    INCLUDE_DIRS 
        "include"
        "address/include"
        "aes/include"
        "base58/include"
        "bignum/include"
        "bip32/include"
        "bip39/include"
        "blake2/include"
        "cardano/include"
        "check_mem/include"
        "curves/include"
        "ecdsa/include"
        "ed25519-donna/include"
        "groestl/include"
        "hasher/include"
        "hmac/include"
        "memzero/include"
        "nist256p1/include"
        "pbkdf2/include"
        "rand/include"
        "rfc6979/include"
        "ripemd160/include"
        "script/include"
        "secp256k1/include"
        "segwit_addr/include"
        "sha/include"
    REQUIRES 
        cmock logger cephes
)