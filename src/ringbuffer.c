#include "ringbuffer.h"

bool bufferIsReadable(struct _kehapuskuri *kehapuskuri)
{
    uint8_t indeksi = kehapuskuri->mIndeksi;
    uint8_t loppu = kehapuskuri->mLoppu;
    uint8_t kierrokset = kehapuskuri->mKierrokset;

    return indeksi != loppu || (kierrokset >> 1) ^ (kierrokset & (uint8_t)0x1);
}

char takeFromBuffer(struct _kehapuskuri *kehapuskuri)
{
    char *puskuri = kehapuskuri->mPuskuri;
    uint8_t indeksi = kehapuskuri->mIndeksi;
    uint8_t kierrokset = kehapuskuri->mKierrokset;
    uint8_t loppu = kehapuskuri->mLoppu;

    char alkio = puskuri[indeksi];

    uint8_t seuraava = indeksi + 1;

    if (indeksi > seuraava)
    {
        kehapuskuri->mKierrokset ^= (uint8_t)(0x1 << 1);
    }

    kehapuskuri->mIndeksi = indeksi != loppu || (kierrokset >> 1) ^ (kierrokset & (uint8_t)0x1) ? seuraava : indeksi;

    return alkio;
}

bool insertToBuffer(struct _kehapuskuri *kehapuskuri, char alkio)
{
    char *puskuri = kehapuskuri->mPuskuri;
    uint8_t indeksi = kehapuskuri->mIndeksi;
    uint8_t kierrokset = kehapuskuri->mKierrokset;
    uint8_t loppu = kehapuskuri->mLoppu;

    if (indeksi == loppu && (kierrokset >> 1) ^ (kierrokset & (uint8_t)0x1))
    {
        return false;
    }

    uint8_t seuraava = loppu + 1;

    if (loppu > seuraava)
    {
        kehapuskuri->mKierrokset ^= (uint8_t)0x1;
    }

    puskuri[loppu] = alkio;

    kehapuskuri->mLoppu = seuraava;

    return true;
}
