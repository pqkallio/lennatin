#include "ringbuffer.h"

bool buffer_is_readable(struct _ringbuffer *ringbuffer)
{
    uint8_t idx = ringbuffer->idx;
    uint8_t end = ringbuffer->end;
    uint8_t rounds = ringbuffer->rounds;

    return idx != end || (rounds >> 1) ^ (rounds & (uint8_t)0x1);
}

char take_from_buffer(struct _ringbuffer *ringbuffer)
{
    char *buf = ringbuffer->buffer;
    uint8_t idx = ringbuffer->idx;
    uint8_t rounds = ringbuffer->rounds;
    uint8_t end = ringbuffer->end;

    char item = buf[idx];

    uint8_t next = idx + 1;

    if (idx > next)
    {
        ringbuffer->rounds ^= (uint8_t)(0x1 << 1);
    }

    ringbuffer->idx = idx != end || (rounds >> 1) ^ (rounds & (uint8_t)0x1) ? next : idx;

    return item;
}

bool insert_into_buffer(struct _ringbuffer *ringbuffer, char item)
{
    char *buf = ringbuffer->buffer;
    uint8_t idx = ringbuffer->idx;
    uint8_t rounds = ringbuffer->rounds;
    uint8_t end = ringbuffer->end;

    if (idx == end && (rounds >> 1) ^ (rounds & (uint8_t)0x1))
    {
        return false;
    }

    uint8_t next = end + 1;

    if (end > next)
    {
        ringbuffer->rounds ^= (uint8_t)0x1;
    }

    buf[end] = item;

    ringbuffer->end = next;

    return true;
}
