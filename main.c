#include <stdio.h>
#include <getopt.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "Obrazek.h"
#include "proc.h"
#include "Wyswietl.h"

int main(int argc, char **argv)
{
    /* Zmienne przechowujace pliki wejscia i wyjscia */
    FILE *output;
    FILE *input;

    /* Deklaracja zmiennych */
    char *ovalue = NULL;
    char *ivalue = NULL;
    char *pvalue = NULL;
    char *gvalue = NULL;
    char kolejka[256];
    int c;
    int kflag = 0;
    int dflag = 0;
    int temp = 0;

    /* Czytanie pokolei argumentow wywolania programu */
    while ((c = getopt (argc, argv, "ni:o:p:g:kd")) != -1)
        switch (c) /* c - wczytany argument */
        {
            /* -n negatyw */
            case 'n':
                kolejka[temp] = 'n'; /* dodaj 'n' do tablicy przechowujacej kolejke wykonania funkcji */
                temp++;
                break;

            /* -i <nazwa_pliku> otwarcie pliku */
            case 'i':
                ivalue = optarg; /* zmienna przechowujaca <nazwa_pliku> */
                break;

            /* -o <nazwa_pliku> podanie nazwy pliku do zapisu */
            case 'o':
                ovalue = optarg; /* zmienna przechowujaca <nazwa_pliku> */
                break;

            /* -p <wartosc> progowanie o podanej wartosci */
            case 'p':
                kolejka[temp] = 'p'; /* dodaj 'p' do tablicy przechowujacej kolejke wykonania funkcji */
                temp++;
                pvalue = optarg; /* zmienna przechowujaca <wartosc> */
                break;

            /* -g <wartosc> korekcja gamma o podanej wartosci */
            case 'g':
                kolejka[temp] = 'g'; /* dodaj 'g' do tablicy przechowujacej kolejke wykonania funkcji */
                temp++;
                gvalue = optarg; /* zmienna przechowujaca <wartosc> */
                break;

            /* -k P3 do P2*/
            case 'k':
                kflag = 1;
                break;

             /* -d Wyswietlenie obrazka */
            case 'd':
                dflag = 1;
                break;

            /* bledne podanie argumentu */
            case '?':
                /* wywolanie opcji bez argumentu */
                if (optopt == 'c')
                    fprintf (stderr, "Opcja -%c wymaga argumentu.\n", optopt);
                /* podanie nieznanej opcji*/
                else if (isprint (optopt))
                    fprintf (stderr, "Nieznana opcja`-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Nieznasy symbol `\\x%x'.\n",
                             optopt);
                return 1;

            default:
                return 2;
        }

    /* Jezeli program zostal wywolany z argumentem -o - */
    if (strcmp(ovalue, "-") == 0)
    {
        output = stdout; /* Przetworzony obrazek zostanie wypisany na standardowe wyjscie */
    }
    else
    {
        output = fopen(ovalue, "w"); /* Przetworzony obrazek zostanie wypisany na podane wyjscie */
    }

    /* Jezeli program zostal wywolany z argumentem -i - */
    if (strcmp(ivalue, "-") == 0)
    {
        input = stdin; /* Przetworzony obrazek zostanie wczytany ze standardoowego wejscia */
    }
    else
    {
        input = fopen(ivalue, "r"); /* Przetworzony obrazek zostanie wczytany z podanego wejscia */
    }

    Obrazek o; /* Utworz obiekt do przechowywania informacji o obrazku */
    ObrazekWczytaj(&o, input); /* Wywolanie funkcji wczytujacej obrazek */

    /* Jezeli program zostal wywolany z argumentem -k i obrazek jest typu P3 */
    if (kflag == 1 && o.Typ == P3)
    {
        ObrazekWypisz(&o, output, 5, 0); /* Konwersja do stopnia szarosci */
        o.Typ = P2; /* Zmien typ obrazka */
    }

    /* Sprawdz kolejke wywolywania funkcji przetwarzania obrazow */
    for (int i = 0; i < temp ; ++i)
    {
        switch(kolejka[i])
        {
            /* Negatyw */
            case 'n':
                ObrazekWypisz(&o, output, 2, 0);
                break;

            /* Progowanie */
            case 'p':
                ObrazekWypisz(&o, output, 3, atof(pvalue));
                break;

            /* Korekcja gamma */
            case 'g':
                ObrazekWypisz(&o, output, 4, atof(gvalue));
                break;

            default:
                printf("Podana bledny parametr");
                break;
        }
    }

    WypiszObrazekNaWyjscie(&o, output); /* Wywolanie funkcji wypisujacej obrazek */

    /* Jesli obrazek zostal zapisany do pliku i program zostal wywowalny z opcja -g to wyswietl obrazek*/
    if (strcmp(ovalue, "-") != 0 && dflag == 1)
    {
        Display(ovalue);
    }

    if (dflag == 1)
    {
        if (strcmp(ovalue, "-") != 0)
        {
            Display(ovalue);
        }
        else
        {
            fprintf(stderr, "Aby wyswietlic obrazek najpierw nalezy go zapisac");
        }
    }


    return 0;
}

/* Autor: Wojciech Konury
 * Nr albumu: 241488
 *
 * Program przetwarzanie obrazow 2 jest pisany od nowa
 *
 * Zrobiono:
 * - Wydzielenie funkcji zwiazanych z obsluga obrazow
 * - Podzielenie programu na odpowiednie moduly
 * - Plik makefile
 * - Wprowadzono odpowiednie struktury danych calosciowo przechowujace informacje o wczytanym obrazie
 *      P2 lub P3 (funkcja automatycznie rozpoznaje typ)
 *      z wykorzystaniem dwuwymiarowych dynamicznych tablic ktora dostosowuja swoje rozmiary
 * - Wprowadzic argumenty wywolania programu
 * - Przygotowac funkcje zapisu programu do pliku
 * - Zdefiniować funkcję konwersji do stopni szarości dla obrazów kolorowych: każdy punkt nowego obrazu
 *      jest średnią arytmetyczną wartości składowych kolorów.
 * - Aseracje (if)
 * - Wyswietlanie zapisanego obrazka -d
 *
 * TODO:
 * - !!! Funkcja pomijania komentarzy !!!
 * - uzupelnic Dokumentacja funkcji
 *
 * TEST1:
 * Cel: Sprawdzenie poprawnoci wykonywania funkcji wczytywania obrazka P2 oraz funkcji przetwarzania na nim
 * Metoda Testowania:
 * - Wczytanie niewielkiego obrazka P2
 * - Wykonanie funkcji przetwarzania
 * Rezultat:
 * - Poprawne wczytanie i wypisanie obrazka wejsciowego
 * - Poprawne wykonanie funkcji przetwarzania i wyswietlenie przetworzonego obrazka
 *
 * TEST2:
 * Cel: Sprawdzenie poprawnosci wykonywania fuunkcji wczytania obrazka P3
 * Metoda testowania:
 * - Wczytanie niewielkiego obrazka P3
 * Rezultat:
 * - Program poprawnie rozpoznaje typ obrazka i zapisuje wartosci kolorow pikseli do specjalnie
 *      zdefiniowanej do tego celu struktury
 * - Poprawne wyswietlenie obrazka P3
*/