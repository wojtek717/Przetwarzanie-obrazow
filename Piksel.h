#ifndef SUPEROBRAZEKKK_PIKSELE_H
#define SUPEROBRAZEKKK_PIKSELE_H

#include <stdbool.h>
#include "Rgb.h"

typedef union
{
    unsigned char Szary; /* Wartosc szarosci danego piksela w obrazku P2 */
    Rgb Rgb; /* Struktura przechowujaca artosci kolorow danego piksela w obrazku P3*/
} Piksel;

bool WczytajSzaryPiksel(FILE *input, Piksel *piksel);
bool WczytajRgbPiksel(FILE *input, Piksel *piksel);

#endif //SUPEROBRAZEKKK_PIKSELE_H
