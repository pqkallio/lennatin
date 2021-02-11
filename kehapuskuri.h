#ifndef KEHAPUSKURI_H_
#define KEHAPUSKURI_H_

static const uint8_t PUSKURIN_KOKO = 256;

template <typename T>
class KehaPuskuri
{
private:
    uint8_t mIndeksi;
    uint8_t mLoppu;
    T mPuskuri[PUSKURIN_KOKO];
    uint8_t mKierrokset;

public:
    KehaPuskuri();
    T ota();
    bool laita(T alkio);
    bool peruOtto();
    bool luettavissa();
};

template <typename T>
KehaPuskuri<T>::KehaPuskuri() : mIndeksi(0), mLoppu(0), mKierrokset(0) {}

template <typename T>
bool KehaPuskuri<T>::luettavissa()
{
    return mIndeksi != mLoppu || (mKierrokset >> 1) ^ (mKierrokset & static_cast<uint8_t>(0x1));
}

template <typename T>
T KehaPuskuri<T>::ota()
{
    T alkio = mPuskuri[mIndeksi];

    uint8_t seuraava = mIndeksi + 1;

    if (mIndeksi > seuraava)
    {
        mKierrokset ^= static_cast<uint8_t>(0x1 << 1);
    }

    mIndeksi = mIndeksi != mLoppu || (mKierrokset >> 1) ^ (mKierrokset & static_cast<uint8_t>(0x1)) ? seuraava : mIndeksi;

    return alkio;
}

template <typename T>
bool KehaPuskuri<T>::peruOtto()
{
    if (mIndeksi == mLoppu && (mKierrokset >> 1) ^ (mKierrokset & static_cast<uint8_t>(0x1)))
    {
        return false;
    }

    uint8_t seuraava = mIndeksi - 1;

    if (seuraava > mIndeksi)
    {
        mKierrokset ^= static_cast<uint8_t>(0x1 << 1);
    }

    mIndeksi = seuraava;

    return true;
}

template <typename T>
bool KehaPuskuri<T>::laita(T alkio)
{
    if (mIndeksi == mLoppu && (mKierrokset >> 1) ^ (mKierrokset & static_cast<uint8_t>(0x1)))
    {
        return false;
    }

    uint8_t seuraava = mLoppu + 1;

    if (mLoppu > seuraava)
    {
        mKierrokset ^= static_cast<uint8_t>(0x1);
    }

    mPuskuri[mLoppu] = alkio;

    mLoppu = seuraava;

    return true;
}

#endif /* KEHAPUSKURI_H_ */
