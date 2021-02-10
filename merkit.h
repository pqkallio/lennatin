#ifndef _LENNATIN_MERKIT_H
#define _LENNATIN_MERKIT_H

#include <cstdint>

namespace merkit
{
    enum Merkki
    {
        AO,
        AE,
        OE,
    };

    std::uint8_t ruotsalainenOO[] = {
        0b00100,
        0b01010,
        0b00100,
        0b01110,
        0b10001,
        0b11111,
        0b10001,
        0b10001,
    };

    std::uint8_t aeae[] = {
        0b01010,
        0b00000,
        0b00100,
        0b01010,
        0b10001,
        0b11111,
        0b10001,
        0b10001,
    };

    std::uint8_t oeoe[] = {
        0b01010,
        0b00000,
        0b01110,
        0b10001,
        0b10001,
        0b10001,
        0b10001,
        0b01110,
    };
} // namespace merkit

#endif /* _LENNATIN_MERKIT_H */
