#include <stdio.h>
#include <math.h>
#include "proc.h"
#include "Obrazek.h"
#include "Piksel.h"

/*  [IN] output - podane przez uzytkownika wyjscie na ktore zostanie wyswietlony przetworzony obrazek
 *  [IN] obrazek - stryktura przechowujaca informacje o otwartym obrazku P2/P3 takie jak:
 *      - dwuwymiarowa tablica zawierajaca wartosci danego piksela w skali szarosci/RGB
 *      - szerokosc i wysokosc obrazka
 *      - maksymalna wartosc danego piksela w skali szarosci/RGB
 *  [IN] x - wspolrzedna szerokosci piksela
 *  [IN] y - wspolrzedna wysokosci piksela*/
void Negatyw(FILE *output, Obrazek *obrazek, int x, int y)
{
    /* Wypisz na podane wyjscie dany piksel w negatywie
     * PikselWNegatywie = MaksymalnyOdcienSzarosciPikseli - OdcienSzarosciPikselaWejsciowego*/
    obrazek->Piksele[y][x].Szary = (obrazek->Skala - obrazek->Piksele[y][x].Szary);
    //fprintf(output, "%hhu\t", (obrazek->Piksele[y][x].Szary));
}

/*  [IN] output - podane przez uzytkownika wyjscie na ktore zostanie wyswietlony przetworzony obrazek
 *  [IN] obrazek - stryktura przechowujaca informacje o otwartym obrazku P2/P3 takie jak:
 *      - dwuwymiarowa tablica zawierajaca wartosci danego piksela w skali szarosci/RGB
 *      - szerokosc i wysokosc obrazka
 *      - maksymalna wartosc danego piksela w skali szarosci/RGB
 *  [IN] x - wspolrzedna szerokosci piksela
 *  [IN] y - wspolrzedna wysokosci piksela
 *  [IN] wartosc - wartosc wykonywanego progowania podanego przez uzytkownika w procentach */
void Progowanie(FILE *output, Obrazek *obrazek, int x, int y, float wartosc)
{
    /* Jezeli OdcienSzarosciPikselaWejsciowego <= MaksymalnyOdcienSzarosci * WartoscProgowaniaWProcentach */
    if(obrazek->Piksele[y][x].Szary <= (int)(obrazek->Skala * (wartosc/100)))
    {
        /* Wypisz na pdane wyjscie piksel o wartosci 0*/
        obrazek->Piksele[y][x].Szary = 0;
        //fprintf(output, "%hhu\t", (obrazek->Piksele[y][x].Szary));
    } else
    {
        /* Wypisz na podane wyjscie wartosc danego piksela = MaksymalnyOdcienSzarosci*/
        obrazek->Piksele[y][x].Szary = obrazek->Skala;
        //fprintf(output, "%hhu\t", (obrazek->Piksele[y][x].Szary));
    }
}

/*  [IN] output - podane przez uzytkownika wyjscie na ktore zostanie wyswietlony przetworzony obrazek
 *  [IN] obrazek - stryktura przechowujaca informacje o otwartym obrazku P2/P3 takie jak:
 *      - dwuwymiarowa tablica zawierajaca wartosci danego piksela w skali szarosci/RGB
 *      - szerokosc i wysokosc obrazka
 *      - maksymalna wartosc danego piksela w skali szarosci/RGB
 *  [IN] x - wspolrzedna szerokosci piksela
 *  [IN] y - wspolrzedna wysokosci piksela
 *  [IN] wartosc - wartosc wykonywanej korekcji gamma */
void KorekcjaGamma(FILE *output, Obrazek *obrazek, int x, int y, float wartosc)
{
    /* Zmienan przechowujaca nowa wartosc piksela */
    float nowyPiksel;

    /* nowaWartoscPiksela =
    * (wartoscWczytanegObrazka / maksymalnyOdcienSzarosci)^(1/parametrGamma)
    * x maksymalnyOdcienSzarosci */
    nowyPiksel= powf(
            (float)obrazek->Piksele[y][x].Szary / (float)obrazek->Skala,
            1 / wartosc
    );
    nowyPiksel*= obrazek->Skala;
    /* Wypisz wartosc danego piksela do pliku */
    obrazek->Piksele[y][x].Szary = ((u_char)nowyPiksel);
    //fprintf(output, "%hhu\t", (obrazek->Piksele[y][x].Szary));
}

/*  [IN] output - podane przez uzytkownika wyjscie na ktore zostanie wyswietlony przetworzony obrazek
 *  [IN] obrazek - stryktura przechowujaca informacje o otwartym obrazku P2/P3 takie jak:
 *      - dwuwymiarowa tablica zawierajaca wartosci danego piksela w skali szarosci/RGB
 *      - szerokosc i wysokosc obrazka
 *      - maksymalna wartosc danego piksela w skali szarosci/RGB
 *  [IN] x - wspolrzedna szerokosci piksela
 *  [IN] y - wspolrzedna wysokosci piksela */
void KonwersjaNaSzarosc(FILE *output, Obrazek *obrazek, int x, int y)
{
    /* Przekonwertowany piksel na skale szarosci ma wartosc sredniej arytmetycznej ze skladowych
     * pikseli obrazka P3 */
    obrazek->Piksele[y][x].Szary = (u_char)((obrazek->Piksele[y][x].Rgb.Red +
                                   obrazek->Piksele[y][x].Rgb.Green +
                                   obrazek->Piksele[y][x].Rgb.Blue) / 3);
}




