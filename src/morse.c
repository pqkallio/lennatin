#include <stddef.h>
#include "morse.h"

// PISTEESTÄ ALKAVAT

// Kuudes taso
static const Morse kysym = {.merkki = 0x3f, .piste = NULL, .viiva = NULL};
static const Morse piste = {.merkki = 0x2e, .piste = NULL, .viiva = NULL};

// Viides taso
static const Morse viisi = {.merkki = 0x35, .piste = NULL, .viiva = NULL};
static const Morse nelja = {.merkki = 0x34, .piste = NULL, .viiva = NULL};
static const Morse kolme = {.merkki = 0x33, .piste = NULL, .viiva = NULL};
static const Morse kysymJohde = {.merkki = 0x00, .piste = &kysym, .viiva = NULL};
static const Morse kaksi = {.merkki = 0x32, .piste = NULL, .viiva = NULL};
static const Morse pisteJohde = {.merkki = 0x00, .piste = NULL, .viiva = &piste};
static const Morse AO = {.merkki = 0xc5, .piste = NULL, .viiva = NULL};
static const Morse yksi = {.merkki = 0x31, .piste = NULL, .viiva = NULL};

// Neljäs taso
static const Morse H = {.merkki = 0x48, .piste = &viisi, .viiva = &nelja};
static const Morse V = {.merkki = 0x56, .piste = NULL, .viiva = &kolme};
static const Morse F = {.merkki = 0x46, .piste = NULL, .viiva = NULL};
static const Morse kaksiJohde = {.merkki = 0x00, .piste = &kysymJohde, .viiva = &kaksi};
static const Morse L = {.merkki = 0x4c, .piste = NULL, .viiva = NULL};
static const Morse AE = {.merkki = 0xc4, .piste = &pisteJohde, .viiva = NULL};
static const Morse P = {.merkki = 0x50, .piste = NULL, .viiva = &AO};
static const Morse J = {.merkki = 0x4a, .piste = NULL, .viiva = &yksi};

// Kolmas taso
static const Morse S = {.merkki = 0x53, .piste = &H, .viiva = &V};
static const Morse U = {.merkki = 0x55, .piste = &F, .viiva = &kaksiJohde};
static const Morse R = {.merkki = 0x52, .piste = &L, .viiva = &AE};
static const Morse W = {.merkki = 0x57, .piste = &P, .viiva = &J};

// Toinen taso
static const Morse I = {.merkki = 0x49, .piste = &S, .viiva = &U};
static const Morse A = {.merkki = 0x41, .piste = &R, .viiva = &W};

// Ensimmäinen taso
static const Morse E = {.merkki = 0x45, .piste = &I, .viiva = &A};

// VIIVASTA ALKAVAT

// Kuudes taso
static const Morse viiva = {.merkki = 0x2d, .piste = NULL, .viiva = NULL};
static const Morse oikeaSulku = {.merkki = 0x29, .piste = NULL, .viiva = NULL};
static const Morse pilkku = {.merkki = 0x2c, .piste = NULL, .viiva = NULL};
static const Morse kaksoispiste = {.merkki = 0x3a, .piste = NULL, .viiva = NULL};

// Viides taso
static const Morse kuusi = {.merkki = 0x36, .piste = NULL, .viiva = &viiva};
static const Morse eqv = {.merkki = 0x3d, .piste = NULL, .viiva = NULL};
static const Morse kautta = {.merkki = 0x2f, .piste = NULL, .viiva = NULL};
static const Morse vasenSulku = {.merkki = 0x28, .piste = NULL, .viiva = &oikeaSulku};
static const Morse seiska = {.merkki = 0x37, .piste = NULL, .viiva = NULL};
static const Morse pilkkuJohde = {.merkki = 0x00, .piste = NULL, .viiva = &pilkku};
static const Morse kasi = {.merkki = 0x38, .piste = &kaksoispiste, .viiva = NULL};
static const Morse ysi = {.merkki = 0x39, .piste = NULL, .viiva = NULL};
static const Morse nolla = {.merkki = 0x30, .piste = NULL, .viiva = NULL};

// Neljäs taso
static const Morse B = {.merkki = 0x42, .piste = &kuusi, .viiva = &eqv};
static const Morse X = {.merkki = 0x58, .piste = &kautta, .viiva = NULL};
static const Morse C = {.merkki = 0x43, .piste = NULL, .viiva = NULL};
static const Morse Y = {.merkki = 0x59, .piste = &vasenSulku, .viiva = NULL};
static const Morse Z = {.merkki = 0x5a, .piste = &seiska, .viiva = &pilkkuJohde};
static const Morse Q = {.merkki = 0x51, .piste = NULL, .viiva = NULL};
static const Morse OE = {.merkki = 0xd6, .piste = &kasi, .viiva = NULL};
static const Morse ysiJohde = {.merkki = 0x00, .piste = &ysi, .viiva = &nolla};

// Kolmas taso
static const Morse D = {.merkki = 0x44, .piste = &B, .viiva = &X};
static const Morse K = {.merkki = 0x4b, .piste = &C, .viiva = &Y};
static const Morse G = {.merkki = 0x47, .piste = &Z, .viiva = &Q};
static const Morse O = {.merkki = 0x4f, .piste = &OE, .viiva = &ysiJohde};

// Toinen taso
static const Morse N = {.merkki = 0x4e, .piste = &D, .viiva = &K};
static const Morse M = {.merkki = 0x4d, .piste = &G, .viiva = &O};

// Ensimmäinen taso
static const Morse T = {.merkki = 0x54, .piste = &N, .viiva = &M};

//JUURI
static const Morse juuri = {.merkki = 0x00, .piste = &E, .viiva = &T};

unsigned char get_char(struct _kehapuskuri *puskuri)
{
    const Morse *morse = &juuri;

    while (bufferIsReadable(puskuri) && morse != NULL)
    {
        char merkki = takeFromBuffer(puskuri);

        switch (merkki)
        {
        case '.':
            morse = morse->piste;
            break;
        case '-':
            morse = morse->viiva;
            break;
        default:
            goto PALAUTUS;
        }
    }

PALAUTUS:
    if (morse == NULL)
    {
        return 0x00;
    }

    return morse->merkki;
}
