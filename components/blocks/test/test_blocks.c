/**
 * Copyright (c) 2023 luisan00 <luisan00@hotmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @brief       Tests for block component
 * @author      luisan00 <luisan00@hotmail.com>
 */
#include <stdint.h>

#include "esp_log.h"
#include "unity.h"

#include "blocks.h"
#include "helpers.h"

static const char tag[] = "[blocks]";

static char *header_blocks[] = {
    "0100000000000000000000000000000000000000000000000000000000000000000000003ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a29ab5f49ffff001d1dac2b7c", // 000
    "010000006fe28c0ab6f1b372c1a6a246ae63f74f931e8365e15a089c68d6190000000000982051fd1e4ba744bbbe680e1fee14677ba1a3c3540bf7b1cdb606e857233e0e61bc6649ffff001d01e36299", // 001
    "010000004860eb18bf1b1620e37e9490fc8a427514416fd75159ab86688e9a8300000000d5fdcc541e25de1c7a5addedf24858b8bb665c9f36ef744ee42c316022c90f9bb0bc6649ffff001d08d2bd61", // 002
    "01000000bddd99ccfda39da1b108ce1a5d70038d0a967bacb68b6b63065f626a0000000044f672226090d85db9a9f2fbfe5f0f9609b387af7be5b7fbb7a1767c831c9e995dbe6649ffff001d05e0ed6d", // 003
    "010000004944469562ae1c2c74d9a535e00b6f3e40ffbad4f2fda3895501b582000000007a06ea98cd40ba2e3288262b28638cec5337c1456aaf5eedc8e9e5a20f062bdf8cc16649ffff001d2bfee0a9", // 004
    "0100000085144a84488ea88d221c8bd6c059da090e88f8a2c99690ee55dbba4e00000000e11c48fecdd9e72510ca84f023370c9a38bf91ac5cae88019bee94d24528526344c36649ffff001d1d03e477", // 005
    "01000000fc33f596f822a0a1951ffdbf2a897b095636ad871707bf5d3162729b00000000379dfb96a5ea8c81700ea4ac6b97ae9a9312b2d4301a29580e924ee6761a2520adc46649ffff001d189c4c97", // 006
    "010000008d778fdc15a2d3fb76b7122a3b5582bea4f21f5a0c693537e7a03130000000003f674005103b42f984169c7d008370967e91920a6a5d64fd51282f75bc73a68af1c66649ffff001d39a59c86", // 007
    "010000004494c8cf4154bdcc0720cd4a59d9c9b285e4b146d45f061d2b6c967100000000e3855ed886605b6d4a99d5fa2ef2e9b0b164e63df3c4136bebf2d0dac0f1f7a667c86649ffff001d1c4b5666", // 008
    "01000000c60ddef1b7618ca2348a46e868afc26e3efc68226c78aa47f8488c4000000000c997a5e56e104102fa209c6a852dd90660a20b2d9c352423edce25857fcd37047fca6649ffff001d28404f53", // 009
    "010000000508085c47cc849eb80ea905cc7800a3be674ffc57263cf210c59d8d00000000112ba175a1e04b14ba9e7ea5f76ab640affeef5ec98173ac9799a852fa39add320cd6649ffff001d1e2de565", // 010
};

TEST_CASE("block version", tag)
{
        uint8_t *blk = from_char_array(header_blocks[10], BLOCK_HEADER_SIZE);
        int32_t expected = 1;
        int32_t result;
        get_block_version(blk, &result);
        TEST_ASSERT_EQUAL_INT32(expected, result);
}

TEST_CASE("previous block hash", tag)
{
    uint8_t *blk = from_char_array(header_blocks[10], BLOCK_HEADER_SIZE);
    uint8_t expected[] = {0x00, 0x00, 0x00, 0x00, 0x8d, 0x9d, 0xc5, 0x10, 0xf2, 0x3c, 0x26, 0x57, 0xfc, 0x4f, 0x67, 0xbe, 0xa3, 0x00, 0x78, 0xcc, 0x05, 0xa9, 0x0e, 0xb8, 0x9e, 0x84, 0xcc, 0x47, 0x5c, 0x08, 0x08, 0x05};
    uint8_t result[__sizeof_previous_hash];
    //get_previous_block_hash(blk, result);    
    //TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, result, ARRAY_SIZEOF(expected));
} 

TEST_CASE("merkle root", tag)
{
    uint8_t *blk = from_char_array(header_blocks[10], BLOCK_HEADER_SIZE);
    uint8_t expected[] = {0xd3, 0xad, 0x39, 0xfa, 0x52, 0xa8, 0x99, 0x97, 0xac, 0x73, 0x81, 0xc9, 0x5e, 0xef, 0xfe, 0xaf, 0x40, 0xb6, 0x6a, 0xf7, 0xa5, 0x7e, 0x9e, 0xba, 0x14, 0x4b, 0xe0, 0xa1, 0x75, 0xa1, 0x2b, 0x11};
    uint8_t result[__sizeof_merkle_root];
    get_merkle_root(blk, result);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, result, ARRAY_SIZEOF(expected));
}

TEST_CASE("block time", tag)
{
    uint8_t *blk = from_char_array(header_blocks[10], BLOCK_HEADER_SIZE);
    uint32_t expected = 1231473952;
    uint32_t result;
    get_block_time(blk, &result);
    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

TEST_CASE("block bits", tag)
{
    uint8_t *blk = from_char_array(header_blocks[10], BLOCK_HEADER_SIZE);
    uint32_t expected = 0x1d00ffff;
    uint32_t result;
    get_block_bits(blk, &result);
    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

TEST_CASE("block nonce", tag)
{
    uint8_t *blk = from_char_array(header_blocks[10], BLOCK_HEADER_SIZE);
    uint32_t expected = 0x65e52d1e;
    uint32_t result;
    get_block_nonce(blk, &result);
    TEST_ASSERT_EQUAL_UINT32(expected, result);
}