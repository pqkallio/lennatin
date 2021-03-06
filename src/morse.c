#include <stddef.h>
#include "morse.h"

// PISTEESTÄ ALKAVAT

// Kuudes taso
static const Morse kysym = {.merkki = 0b00111111, .piste = NULL, .viiva = NULL};
static const Morse piste = {.merkki = 0b00101110, .piste = NULL, .viiva = NULL};

// Viides taso
static const Morse viisi = {.merkki = 0b00110101, .piste = NULL, .viiva = NULL};
static const Morse nelja = {.merkki = 0b00110100, .piste = NULL, .viiva = NULL};
static const Morse kolme = {.merkki = 0b00110011, .piste = NULL, .viiva = NULL};
static const Morse kysymJohde = {.merkki = 0b00000000, .piste = &kysym, .viiva = NULL};
static const Morse kaksi = {.merkki = 0b00110010, .piste = NULL, .viiva = NULL};
static const Morse pisteJohde = {.merkki = 0b00000000, .piste = NULL, .viiva = &piste};
static const Morse AO = {.merkki = 0b11000101, .piste = NULL, .viiva = NULL};
static const Morse yksi = {.merkki = 0b00110001, .piste = NULL, .viiva = NULL};

// Neljäs taso
static const Morse H = {.merkki = 0b01001000, .piste = &viisi, .viiva = &nelja};
static const Morse V = {.merkki = 0b01010110, .piste = NULL, .viiva = &kolme};
static const Morse F = {.merkki = 0b01000110, .piste = NULL, .viiva = NULL};
static const Morse kaksiJohde = {.merkki = 0b00000000, .piste = &kysymJohde, .viiva = &kaksi};
static const Morse L = {.merkki = 0b01001100, .piste = NULL, .viiva = NULL};
static const Morse AE = {.merkki = 0b11000100, .piste = &pisteJohde, .viiva = NULL};
static const Morse P = {.merkki = 0b01010000, .piste = NULL, .viiva = &AO};
static const Morse J = {.merkki = 0b01001010, .piste = NULL, .viiva = &yksi};

// Kolmas taso
static const Morse S = {.merkki = 0b01010011, .piste = &H, .viiva = &V};
static const Morse U = {.merkki = 0b01010101, .piste = &F, .viiva = &kaksiJohde};
static const Morse R = {.merkki = 0b01010010, .piste = &L, .viiva = &AE};
static const Morse W = {.merkki = 0b01010111, .piste = &P, .viiva = &J};

// Toinen taso
static const Morse I = {.merkki = 0b01001001, .piste = &S, .viiva = &U};
static const Morse A = {.merkki = 0b01000001, .piste = &R, .viiva = &W};

// Ensimmäinen taso
static const Morse E = {.merkki = 0b01000101, .piste = &I, .viiva = &A};

// VIIVASTA ALKAVAT

// Kuudes taso
static const Morse viiva = {.merkki = 0b00101101, .piste = NULL, .viiva = NULL};
static const Morse oikeaSulku = {.merkki = 0b00101001, .piste = NULL, .viiva = NULL};
static const Morse pilkku = {.merkki = 0b00101100, .piste = NULL, .viiva = NULL};
static const Morse kaksoispiste = {.merkki = 0b00111010, .piste = NULL, .viiva = NULL};

// Viides taso
static const Morse kuusi = {.merkki = 0b00110110, .piste = NULL, .viiva = &viiva};
static const Morse eqv = {.merkki = 0b00111101, .piste = NULL, .viiva = NULL};
static const Morse kautta = {.merkki = 0b00101111, .piste = NULL, .viiva = NULL};
static const Morse vasenSulku = {.merkki = 0b00101000, .piste = NULL, .viiva = &oikeaSulku};
static const Morse seiska = {.merkki = 0b00110111, .piste = NULL, .viiva = NULL};
static const Morse pilkkuJohde = {.merkki = 0b00000000, .piste = NULL, .viiva = &pilkku};
static const Morse kasi = {.merkki = 0b00111000, .piste = &kaksoispiste, .viiva = NULL};
static const Morse ysi = {.merkki = 0b00111001, .piste = NULL, .viiva = NULL};
static const Morse nolla = {.merkki = 0b00110000, .piste = NULL, .viiva = NULL};

// Neljäs taso
static const Morse B = {.merkki = 0b01000010, .piste = &kuusi, .viiva = &eqv};
static const Morse X = {.merkki = 0b01011000, .piste = &kautta, .viiva = NULL};
static const Morse C = {.merkki = 0b01000011, .piste = NULL, .viiva = NULL};
static const Morse Y = {.merkki = 0b01011001, .piste = &vasenSulku, .viiva = NULL};
static const Morse Z = {.merkki = 0b01011010, .piste = &seiska, .viiva = &pilkkuJohde};
static const Morse Q = {.merkki = 0b01010001, .piste = NULL, .viiva = NULL};
static const Morse OE = {.merkki = 0b11010110, .piste = &kasi, .viiva = NULL};
static const Morse ysiJohde = {.merkki = 0b00000000, .piste = &ysi, .viiva = &nolla};

// Kolmas taso
static const Morse D = {.merkki = 0b01000100, .piste = &B, .viiva = &X};
static const Morse K = {.merkki = 0b01001011, .piste = &C, .viiva = &Y};
static const Morse G = {.merkki = 0b01000111, .piste = &Z, .viiva = &Q};
static const Morse O = {.merkki = 0b01001111, .piste = &OE, .viiva = &ysiJohde};

// Toinen taso
static const Morse N = {.merkki = 0b01001110, .piste = &D, .viiva = &K};
static const Morse M = {.merkki = 0b01001101, .piste = &G, .viiva = &O};

// Ensimmäinen taso
static const Morse T = {.merkki = 0b01010100, .piste = &N, .viiva = &M};

//JUURI
static const Morse juuri = {.merkki = 0b00000000, .piste = &E, .viiva = &T};

unsigned char haeKirjain(struct _kehapuskuri *puskuri)
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
    return 0b00000000;
  }

  return morse->merkki;
}
