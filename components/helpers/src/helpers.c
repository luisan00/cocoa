#include "helpers.h"

//
uint8_t hex(char ch)
{
    uint8_t r = (ch > 57) ? (ch - 55) : (ch - 48);
    return r & 0x0F;
}

//
size_t to_byte_array(const char *in, size_t in_size, uint8_t *out)
{
    size_t count = 0;
    if (in_size % 2)
    {
        while (*in && out)
        {
            *out = hex(*in++);
            if (!*in)
                return count;
            *out = (*out << 4) | hex(*in++);
            *out++;
            count++;
        }
        return count;
    }
    else
    {
        while (*in && out)
        {
            *out++ = (hex(*in++) << 4) | hex(*in++);
            count++;
        }
        return count;
    }
}