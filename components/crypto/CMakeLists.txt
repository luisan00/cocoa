file(GLOB RECURSE LIB_BASE58 base58/*.c)
file(GLOB RECURSE LIB_BIP32 bip32/*.c)
file(GLOB RECURSE LIB_BIP39 bip39/*.c)
file(GLOB_RECURSE LIB_MEMZERO memzero/*.c)

idf_component_register(
    SRCS 
        ${LIB_BASE58}
        ${LIB_BIP32}
        ${LIB_BIP39}
        ${LIB_MEMZERO}
    INCLUDE_DIRS 
        "include"
        "base58/include"
        "bip32/include"
        "bip39/include"
        "memzero/include"
    REQUIRES 
        cmock
)