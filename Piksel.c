#include <stdio.h>
#include "Piksel.h"

/*  [IN] input - podany przez uzytkownika plik(obrazek P2/P3) ktory ma zostac wczytany i przetworzony
 *  [OUT] piksel - wartosc danego piksela w skali szarosci
 *  [RETURN] czy wczytanie piksela sie powiodlo
 *  Aseracje wykonywane sa w funkcji ObrazekWczytaj()*/
bool WczytajSzaryPiksel(FILE *input, Piksel *piksel)
{
    return (bool)fscanf(input, "%hhu", &piksel->Szary); /* Wczytaj wartosc odcienia szarosci */

};

/*  [IN] input - podany przez uzytkownika plik(obrazek P2/P3) ktory ma zostac wczytany i przetworzony
 *  [OUT] piksel - struktura przechowujaca informacje o wartosciach kolorow danego piksela,
 *      wartosc pojedynczego piksela sklada sie z trzech podstawowych kolorow RGB
 *  [RETURN] czy wczytanie piksela sie powiodlo
 *  Aseracje wykonywane sa w funkcji ObrazekWczytaj()*/
bool WczytajRgbPiksel(FILE *input, Piksel *piksel)
{
    if
            (
            fscanf(input, "%hhu", &piksel->Rgb.Red) && /* Wczytaj wartosc czerwonego koloru */
            fscanf(input, "%hhu", &piksel->Rgb.Green) && /* Wczytaj wartosc zielonego koloru */
            fscanf(input, "%hhu", &piksel->Rgb.Blue) /* Wczytaj wartosc niebieskiego koloru */
            )
    {
        return true;
    }
    else
    {
        return false;
    }
}