#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H
#include <stdint.h>

typedef struct {
    uint8_t bytes[2];
} slice_vector_t;

/*
 * uint8_t in[] = {0x00, 0x00, 0xca, 0xfe, 0x00, 0x00, 0xbe, 0xef, 0x00, 0x00, 0xfe, 0xed, 0x00, 0x00};
 */
static const slice_vector_t slice_expected[] = {
    {{0x00, 0x00}}, {{0x00, 0xca}}, {{0xca, 0xfe}}, {{0xfe, 0x00}}, {{0x00, 0x00}}, {{0x00, 0xbe}},
    {{0xbe, 0xef}}, {{0xef, 0x00}}, {{0x00, 0x00}}, {{0x00, 0xfe}}, {{0xfe, 0xed}}, {{0xed, 0x00}},
};

#endif // TEST_HELPERS_H