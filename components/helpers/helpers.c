#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "helpers.h"

char hex_lookup[] = "0123456789abcdef";

uint8_t from_char(const char *b)
{
    return (uint8_t)strtoul(b, NULL, 16);
}

uint8_t *from_char_array(const char *in, size_t out_len)
{
    uint8_t *out = malloc(out_len * sizeof(uint8_t));
    for (size_t i = 0; i < out_len; i++)
    {
        char cc[3];
        sprintf(cc, "%c%c", in[i * 2], in[i * 2 + 1]);
        out[i] = from_char(cc);
    }
    return out;
    free(out);
}

char *from_u8(uint8_t in)
{
    char *_out = (char *)malloc(2 + 1);

    sprintf(_out, "%02x", in);
    return _out;
    free(_out);
}

void from_u8_array(uint8_t *in, size_t in_size, char *out, size_t out_size)
{
    char _str[out_size];
    memset(_str, '\0', out_size);

    for (size_t i = 0; i < in_size; i++)
    {
        _str[(i * 2) + 0] = hex_lookup[((in[i] & 0xF0) >> 4)];
        _str[(i * 2) + 1] = hex_lookup[((in[i] & 0x0F) >> 0)];
    }
    memcpy(out, _str, out_size);

}

uint8_t *slice_u8(uint8_t *arr, int pos, size_t len)
{
    uint8_t *buff = (uint8_t *)malloc(len * sizeof(uint8_t));

    for (size_t i = 0; i < len; i++)
    {
        buff[i] = arr[pos + i];
    }
    return buff;
    free(buff);
}

uint8_t *flip_u8(uint8_t *buff, size_t buff_size)
{
    uint8_t *flip_buff = (uint8_t *)malloc(buff_size * sizeof(uint8_t));

    size_t i = 0;

    while (i < buff_size)
    {
        flip_buff[i] = buff[buff_size - i - 1];
        i++;
    }
    return flip_buff;
    free(flip_buff);
}
