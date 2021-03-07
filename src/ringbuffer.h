#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#include <stdbool.h>
#include <stdint.h>

struct _ringbuffer
{
    uint8_t idx;
    uint8_t end;
    char *buffer;
    uint8_t rounds;
};

bool buffer_is_readable(struct _ringbuffer *ringbuffer);
char take_from_buffer(struct _ringbuffer *ringbuffer);
bool insert_into_buffer(struct _ringbuffer *ringbuffer, char item);

#endif /* _RINGBUFFER_H */
