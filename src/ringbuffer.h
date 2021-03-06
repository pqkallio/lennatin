#ifndef _KEHAPUSKURI_H
#define _KEHAPUSKURI_H

#include <stdbool.h>
#include <stdint.h>

struct _kehapuskuri
{
    uint8_t mIndeksi;
    uint8_t mLoppu;
    char *mPuskuri;
    uint8_t mKierrokset;
};

bool bufferIsReadable(struct _kehapuskuri *kehapuskuri);
char takeFromBuffer(struct _kehapuskuri *kehapuskuri);
bool insertToBuffer(struct _kehapuskuri *kehapuskuri, char alkio);

#endif /* _KEHAPUSKURI_H */
