#ifndef MORSE_H_
#define MORSE_H_

#include <string>
#include "kehapuskuri.h"
#include "merkit.h"

typedef struct _morse
{
    char merkki;
    const struct _morse *piste;
    const struct _morse *viiva;
} Morse;

// PISTEESTÄ ALKAVAT

// Kuudes taso
static const Morse kysym = {.merkki = '?', .piste = nullptr, .viiva = nullptr};
static const Morse piste = {.merkki = '.', .piste = nullptr, .viiva = nullptr};

// Viides taso
static const Morse viisi = {.merkki = '5', .piste = nullptr, .viiva = nullptr};
static const Morse nelja = {.merkki = '4', .piste = nullptr, .viiva = nullptr};
static const Morse kolme = {.merkki = '3', .piste = nullptr, .viiva = nullptr};
static const Morse kysymJohde = {.merkki = '\0', .piste = &kysym, .viiva = nullptr};
static const Morse kaksi = {.merkki = '2', .piste = nullptr, .viiva = nullptr};
static const Morse pisteJohde = {.merkki = '\0', .piste = nullptr, .viiva = &piste};
static const Morse AO = {.merkki = merkit::AO, .piste = nullptr, .viiva = nullptr};
static const Morse yksi = {.merkki = '1', .piste = nullptr, .viiva = nullptr};

// Neljäs taso
static const Morse H = {.merkki = 'H', .piste = &viisi, .viiva = &nelja};
static const Morse V = {.merkki = 'V', .piste = nullptr, .viiva = &kolme};
static const Morse F = {.merkki = 'F', .piste = nullptr, .viiva = nullptr};
static const Morse kaksiJohde = {.merkki = '\0', .piste = &kysymJohde, .viiva = &kaksi};
static const Morse L = {.merkki = 'L', .piste = nullptr, .viiva = nullptr};
static const Morse AE = {.merkki = merkit::AE, .piste = &pisteJohde, .viiva = nullptr};
static const Morse P = {.merkki = 'P', .piste = nullptr, .viiva = &AO};
static const Morse J = {.merkki = 'J', .piste = nullptr, .viiva = &yksi};

// Kolmas taso
static const Morse S = {.merkki = 'S', .piste = &H, .viiva = &V};
static const Morse U = {.merkki = 'U', .piste = &F, .viiva = &kaksiJohde};
static const Morse R = {.merkki = 'R', .piste = &L, .viiva = &AE};
static const Morse W = {.merkki = 'W', .piste = &P, .viiva = &J};

// Toinen taso
static const Morse I = {.merkki = 'I', .piste = &S, .viiva = &U};
static const Morse A = {.merkki = 'A', .piste = &R, .viiva = &W};

// Ensimmäinen taso
static const Morse E = {.merkki = 'E', .piste = &I, .viiva = &A};

// VIIVASTA ALKAVAT

// Kuudes taso
static const Morse viiva = {.merkki = '-', .piste = nullptr, .viiva = nullptr};
static const Morse oikeaSulku = {.merkki = ')', .piste = nullptr, .viiva = nullptr};
static const Morse pilkku = {.merkki = ',', .piste = nullptr, .viiva = nullptr};
static const Morse kaksoispiste = {.merkki = ':', .piste = nullptr, .viiva = nullptr};

// Viides taso
static const Morse kuusi = {.merkki = '6', .piste = nullptr, .viiva = &viiva};
static const Morse eqv = {.merkki = '=', .piste = nullptr, .viiva = nullptr};
static const Morse kautta = {.merkki = '/', .piste = nullptr, .viiva = nullptr};
static const Morse vasenSulku = {.merkki = '(', .piste = nullptr, .viiva = &oikeaSulku};
static const Morse seiska = {.merkki = '7', .piste = nullptr, .viiva = nullptr};
static const Morse pilkkuJohde = {.merkki = '\0', .piste = nullptr, .viiva = &pilkku};
static const Morse kasi = {.merkki = '8', .piste = &kaksoispiste, .viiva = nullptr};
static const Morse ysi = {.merkki = '9', .piste = nullptr, .viiva = nullptr};
static const Morse nolla = {.merkki = '0', .piste = nullptr, .viiva = nullptr};

// Neljäs taso
static const Morse B = {.merkki = 'B', .piste = &kuusi, .viiva = &eqv};
static const Morse X = {.merkki = 'X', .piste = &kautta, .viiva = nullptr};
static const Morse C = {.merkki = 'C', .piste = nullptr, .viiva = nullptr};
static const Morse Y = {.merkki = 'Y', .piste = &vasenSulku, .viiva = nullptr};
static const Morse Z = {.merkki = 'Z', .piste = &seiska, .viiva = &pilkkuJohde};
static const Morse Q = {.merkki = 'Q', .piste = nullptr, .viiva = nullptr};
static const Morse OE = {.merkki = merkit::OE, .piste = &kasi, .viiva = nullptr};
static const Morse ysiJohde = {.merkki = '\0', .piste = &ysi, .viiva = &nolla};

// Kolmas taso
static const Morse D = {.merkki = 'D', .piste = &B, .viiva = &X};
static const Morse K = {.merkki = 'K', .piste = &C, .viiva = &Y};
static const Morse G = {.merkki = 'G', .piste = &Z, .viiva = &Q};
static const Morse O = {.merkki = 'O', .piste = &OE, .viiva = &ysiJohde};

// Toinen taso
static const Morse N = {.merkki = 'N', .piste = &D, .viiva = &K};
static const Morse M = {.merkki = 'M', .piste = &G, .viiva = &O};

// Ensimmäinen taso
static const Morse T = {.merkki = 'T', .piste = &N, .viiva = &M};

//JUURI
static const Morse juuri = {.merkki = '\0', .piste = &E, .viiva = &T};

char haeKirjain(KehaPuskuri<char> &puskuri)
{
    const Morse *morse = &juuri;

    while (puskuri.luettavissa() && morse != nullptr)
    {
        char merkki = puskuri.ota();

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
    if (morse == nullptr)
    {
        return '\0';
    }

    return morse->merkki;
}

#endif /* MORSE_H_ */
