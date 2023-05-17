# Cocoa (WIP)

## Project status by component


- [X] blocks [tests passed](./components/blocks/test/test_blocks.c)

- [ ] cephes [WIP](./components/cephes/test/test_gamma.c)

- [ ] **crypto**
  - [ ] address [WIP] Unitary test under development
  - [ ] aes
  - [X] base58 [tests passed](./components/crypto/test/test_base58.c)
  - [ ] bignum [WIP]
  - [X] bip32
    
    - [test-vector-1](./components/crypto/test/test_v1_bip32.c)
    - [test-vector-2](./components/crypto/test/test_v2_bip32.c)
    - [test-vector-3](./components/crypto/test/test_v3_bip32.c)
    - [test-vector-4](./components/crypto/test/test_v4_bip32.c)
    - [test_compare](./components/crypto/test/test_compare_bip32.c)
    - [test_optimized](./components/crypto/test/test_optimized_bip32.c)

  - [ ] bip39: [WIP] Unitary tests under development
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
  - [ ] rfc6979
  - [ ] ripemd160
  - [ ] script
  - [ ] secp256k1
  - [X] segwit_addr [test](./components/crypto/test/test_segwit_addr.c)
  - [ ] sha

- [X] **helpers**

- [ ] **hmi**

- [ ] **screen**

- [ ] **storage** [WIP Under development](./components/storage/test/test_storage.c)

## License

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 or in the LICENSE file, in the root folder of this repository.

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

See the License for the specific language governing permissions and limitations under the License.

Copyright (c) 2022 Luis A. Ruiz <luisan00@hotmail.com>

Licensed under the Apache License Version 2.0 Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
