# Cocoa (WIP)

Trezor for Esp32 with a special emphasis on the generation of random numbers and the statistical detection of non-random patterns.

> Statistical tests for random numbers is a series of test to check if a given sequence of bits can be (or not) considered as random.

| Test name                             | Status |
|:--------------------------------------|:------:|
| Frequency test (monobit)              | [done](components/crypto/rand/statistical.c#L12)  |
| Frequency test within a block         | [done](components/crypto/rand/statistical.c#L25)  |
| Runs test                             | [done](components/crypto/rand/statistical.c#L42)  |
| Longest run of ones                   | [done](components/crypto/rand/statistical.c#L73)  |
| Matrix rank test                      | [done](components/crypto/rand/statistical.c#L164) |
| Discrete Fourier Transform (Spectral) | [done](components/crypto/rand/statistical.c#L235) |
| Non-overlapping Template Matching     | [done](components/crypto/rand/statistical.c#L283) |
| Overlapping Template Matching         | WIP    |
| Maurer’s “Universal Statistical”      | -      |
| Linear Complexity                     | -      |
| Serial                                | -      |
| Approximate Entropy                   | -      |
| Cumulative Sums (Cusum)               | -      |
| Random Excursions Variant             | -      |   

see [components/crypto/rand/include/statistical.h](components/crypto/rand/include/statistical.h)

## Project status by component

- [X] blocks [tests passed](./components/blocks/test/test_blocks.c)

```
Block header decoder
```

- [ ] **crypto**

```
`This series of libraries are platform agnostic so no much to do here, minor changes to work on esp32.
 The greatest work is on the random statistical library and the adaptation of unitary tests
```

  - [ ] address [WIP] Unitary test under development
  - [ ] aes
  - [X] base58 [done](./components/crypto/test/test_base58.c)
  - [ ] bignum [WIP](./components/crypto/test/test_bignum.c)
  - [X] bip32 [done]
    
    - [test-vector-1](./components/crypto/test/test_v1_bip32.c)
    - [test-vector-2](./components/crypto/test/test_v2_bip32.c)
    - [test-vector-3](./components/crypto/test/test_v3_bip32.c)
    - [test-vector-4](./components/crypto/test/test_v4_bip32.c)
    - [test_compare](./components/crypto/test/test_compare_bip32.c)
    - [test_optimized](./components/crypto/test/test_optimized_bip32.c)

  - [X] bip39: [done](./components/crypto/test/test_bip39.c)
  - [ ] blake2
  - [ ] cardano
  - [ ] check_mem
  - [ ] curves: [WIP]
  - [ ] ed25519-donna
  - [ ] groestl
  - [ ] hasher [WIP]
  - [ ] hmac [WIP]
  - [ ] memzero [WIP]: Unitary test under development
  - [ ] nist256p1
  - [ ] pkdf2
  - [ ] rand: [WIP statistical tests](./components/crypto/test/test_v1_rand.c) 
  - [ ] rfc6979 [WIP](components/crypto/rfc6979)
  - [ ] ripemd160 [WIP](./components/crypto/ripemd160)
  - [ ] script [WIP](./components/crypto/script)
  - [ ] secp256k1 [WIP](./components/crypto/secp256k1)
  - [X] segwit_addr [done](./components/crypto/test/test_segwit_addr.c)
  - [X] sha [done](./components/crypto/test/test_sha.c)

- [X] **helpers**

- [ ] **hmi** [WIP](components/hmi/test/test_hmi.c)

- [ ] **screen**

- [ ] **storage** [WIP Under development](./components/storage/test/test_storage.c)

## License

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 or in the LICENSE file, in the root folder of this repository.

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

See the License for the specific language governing permissions and limitations under the License.

Copyright (c) 2022 Luis A. Ruiz <luisan00@hotmail.com>

Licensed under the Apache License Version 2.0 Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
