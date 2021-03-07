#ifndef _MORSE_H
#define _MORSE_H

#include "ringbuffer.h"

typedef struct _morse
{
    unsigned char ch;
    const struct _morse *dot;
    const struct _morse *dash;
} Morse;

unsigned char get_char(struct _ringbuffer *buf);

#endif /* _MORSE_H */
