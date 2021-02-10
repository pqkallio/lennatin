#ifndef KEHAPUSKURI_H_
#define KEHAPUSKURI_H_

#include <cstdint>

static const std::size_t PUSKURIN_KOKO = 256;

template <typename T>
class KehaPuskuri
{
private:
    std::uint_fast8_t mIndeksi;
    std::uint_fast8_t mLoppu;
    T mPuskuri[PUSKURIN_KOKO];
    std::uint_fast8_t mKierrokset;

public:
    KehaPuskuri();
    T ota();
    bool laita(T alkio);
    bool luettavissa();
};

template <typename T>
KehaPuskuri<T>::KehaPuskuri() : mIndeksi(0), mLoppu(0), mKierrokset(0) {}

template <typename T>
bool KehaPuskuri<T>::luettavissa()
{
    return mIndeksi != mLoppu || (mKierrokset >> 1) ^ mKierrokset & static_cast<std::uint_fast8_t>(0x1);
}

template <typename T>
T KehaPuskuri<T>::ota()
{
    T alkio = mPuskuri[mIndeksi];

    std::uint_fast8_t seuraava = static_cast<std::uint_fast8_t>((mIndeksi + 1) % PUSKURIN_KOKO);

    if (mIndeksi > seuraava)
    {
        mKierrokset ^= static_cast<std::uint_fast8_t>(0x1 << 1);
    }

    mIndeksi = mIndeksi != mLoppu || (mKierrokset >> 1) ^ mKierrokset & static_cast<std::uint_fast8_t>(0x1) ? seuraava : mIndeksi;

    return alkio;
}

template <typename T>
bool KehaPuskuri<T>::laita(T alkio)
{
    if (mIndeksi == mLoppu && (mKierrokset >> 1) ^ mKierrokset & static_cast<std::uint_fast8_t>(0x1))
    {
        return false;
    }

    std::uint_fast8_t seuraava = static_cast<std::uint_fast8_t>((mLoppu + 1) % PUSKURIN_KOKO);

    if (mLoppu > seuraava)
    {
        mKierrokset ^= static_cast<std::uint_fast8_t>(0x1);
    }

    mPuskuri[mLoppu] = alkio;

    mLoppu = seuraava;

    return true;
}

#endif /* KEHAPUSKURI_H_ */
