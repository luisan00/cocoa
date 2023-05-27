#ifndef TEST_BIP39_H
#define TEST_BIP39_H

typedef struct {
    const char *mnemonic;
    const char *bits;
} test_bip39_t;

static const char *vectors_ok[] = {
    "abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon about",
    "legal winner thank year wave sausage worth useful legal winner thank yellow",
    "letter advice cage absurd amount doctor acoustic avoid letter advice cage above",
};
static const char *vectors_fail[] = {
    "above abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon about",
    "above winner thank year wave sausage worth useful legal winner thank yellow",
    "above advice cage absurd amount doctor acoustic avoid letter advice cage above",
};

test_bip39_t bip39_data[] = {
    {"abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon "
     "about",
     "00000000000000000000000000000000"},
    {"legal winner thank year wave sausage worth useful legal winner thank yellow",
     "7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f"},
    {"letter advice cage absurd amount doctor acoustic avoid letter advice cage above",
     "80808080808080808080808080808080"},
    {"board blade invite damage undo sun mimic interest slam gaze truly inherit resist great "
     "inject rocket museum chief",
     "18a2e1d81b8ecfb2a333adcb0c17a5b9eb76cc5d05db91a4"},
    {"beyond stage sleep clip because twist token leaf atom beauty genius food business side grid "
     "unable middle armed observe pair crouch tonight away coconut",
     "15da872c95a13dd738fbf50e427583ad61f18fd99f628c417a61cf8343c90419"},
};

#endif
