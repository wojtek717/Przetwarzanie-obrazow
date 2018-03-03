#ifndef SUPEROBRAZEKKK_OBRAZEK_H
#define SUPEROBRAZEKKK_OBRAZEK_H

#include "TypObrazka.h"
#include "Piksel.h"

/* Struktura przechowujaca informacje o wczytanym obrazku */
typedef struct
{
    TypObrazka Typ; /* Magiczna liczba obrazka P2/P3 */
    unsigned int WymX; /* Szerokosc obrazka*/
    unsigned int WymY; /* Wysokosc obrazka */
    unsigned char Skala; /* Maksymalna wartosc szarosci/koloru pojedynczego piksela */

    /*Dwuwymiarowa dynamiczna tablica typu Piksel przechowujaca
     * struktury z informacjami o wartosci szarosci/koloru danego piksela*/
    Piksel **Piksele;

} Obrazek;

void PominiecieKomentarzy(FILE  *input);
bool ObrazekWczytaj(Obrazek *obrazek, FILE *input);
void ObrazekWypisz(Obrazek *obrazek, FILE *output, int wybor, float wartosc);
void WypiszObrazekNaWyjscie(Obrazek *obrazek, FILE *output);


#endif //SUPEROBRAZEKKK_OBRAZEK_H
