#ifndef _MORSE_H
#define _MORSE_H

#include "ringbuffer.h"

typedef struct _morse
{
    unsigned char merkki;
    const struct _morse *piste;
    const struct _morse *viiva;
} Morse;

unsigned char get_char(struct _kehapuskuri *puskuri);

#endif /* _MORSE_H */
