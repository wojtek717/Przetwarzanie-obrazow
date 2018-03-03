#ifndef SUPEROBRAZEKKK_PROC_H
#define SUPEROBRAZEKKK_PROC_H

#include "Obrazek.h"

void Negatyw(FILE *output, Obrazek *obrazek, int x, int y);
void Progowanie(FILE *output, Obrazek *obrazek, int x, int y, float wartosc);
void KorekcjaGamma(FILE *output, Obrazek *obrazek, int x, int y, float wartosc);
void KonwersjaNaSzarosc(FILE *output, Obrazek *obrazek, int x, int y);

#endif //SUPEROBRAZEKKK_PROC_H
