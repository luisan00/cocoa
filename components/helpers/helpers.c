#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

#include "esp_log.h"
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
        snprintf(cc, sizeof(cc), "%c%c", in[i * 2], in[i * 2 + 1]);
        out[i] = from_char(cc);
    }
    return out;
    free(out);
}

char *from_u8(uint8_t in)
{
    char *_out = (char *)malloc(2 + 1);
    snprintf(_out, 3UL, "%02x", in);
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

const uint8_t *fromhex(const char *str)
{
    static uint8_t buf[FROMHEX_MAXLEN];
    size_t len = strlen(str) / 2;
    if (len > FROMHEX_MAXLEN)
        len = FROMHEX_MAXLEN;
    for (size_t i = 0; i < len; i++)
    {
        uint8_t c = 0;
        if (str[i * 2] >= '0' && str[i * 2] <= '9')
            c += (str[i * 2] - '0') << 4;
        if ((str[i * 2] & ~0x20) >= 'A' && (str[i * 2] & ~0x20) <= 'F')
            c += (10 + (str[i * 2] & ~0x20) - 'A') << 4;
        if (str[i * 2 + 1] >= '0' && str[i * 2 + 1] <= '9')
            c += (str[i * 2 + 1] - '0');
        if ((str[i * 2 + 1] & ~0x20) >= 'A' && (str[i * 2 + 1] & ~0x20) <= 'F')
            c += (10 + (str[i * 2 + 1] & ~0x20) - 'A');
        buf[i] = c;
    }
    return buf;
}

const char *tohex(uint8_t *in, size_t in_size)
{
    static char str[FROMHEX_MAXLEN];
    from_u8_array(in, in_size, str, in_size * 2 + 1);
    return (const char *)str;
}

//
bool equal_u8(const uint8_t byte1, const uint8_t byte2)
{
    if (byte1 != byte2)
    {
        return false;
    }
    return true;
}

//
bool equal_u8_array(const uint8_t *arr_1, const uint8_t *arr_2, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (!equal_u8(arr_1[i], arr_2[i]))
        {
            return false;
        }
    }
    return true;
}

//
bool equal_char(char _c1, char _c2)
{
    if (_c1 != _c2)
    {
        return false;
    }
    return true;
}

//
bool equal_char_array(const char *_s1, const char *_s2, size_t _len)
{
    for (size_t i = 0; i < _len; i++)
    {
        if (!equal_char(_s1[i], _s2[i]))
        {
            return false;
        }
    }
    return true;
}