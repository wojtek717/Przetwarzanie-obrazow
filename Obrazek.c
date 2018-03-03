#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Obrazek.h"
#include "Piksel.h"
#include "proc.h"

/* Tutaj bedzie funkcja pomijajaca komentarze w obrazku*/
void PominiecieKomentarzy(FILE  *input)
{

}

/*  [IN] obrazek - stryktura przechowujaca informacje o otwartym obrazku P2/P3 takie jak:
 *      - dwuwymiarowa tablica zawierajaca wartosci danego piksela w skali szarosci/RGB
 *      - szerokosc i wysokosc obrazka
 *      - maksymalna wartosc danego piksela w skali szarosci/RGB
 *  [IN] output - podane przez uzytkownika wyjscie na ktore zostanie wyswietlony przetworzony obrazek
 *  [IN] wybor - podana przez uzytkownika wartosc ktora definiuje odpowiednia funkcje przetwarzania obrazka
 *  [IN] wartosc - podana przez uzytkownika wartosc wykonania danej funkcji */
void ObrazekWypisz(Obrazek *obrazek, FILE *output, int wybor, float wartosc)
{
    /* Przejdz po wszystkich elementach(pikselach) obrazka */
    for (int y = 0; y < obrazek->WymY; ++y)
    {
        for (int x = 0; x < obrazek->WymX; ++x)
        {
            /* Wykonaj odpowiednie operacje na obrazku w zaleznosci od jego typu*/
            switch (obrazek->Typ)
            {
                case P2: /* Obrazek w skali szarosci */
                    /* Wykonaj odpowiednie operacje na obrazku w zaleznosci od podanych parametrow */
                    switch (wybor)
                    {
                        case 1:
                            /* Wypisz na pdane wyjscie przetworzony obrazek */
                            fprintf(output, "%hhu\t", obrazek->Piksele[y][x].Szary);
                            break;

                        case 2:
                            Negatyw(output, obrazek, x, y);
                            break;

                        case 3:
                            Progowanie(output, obrazek, x, y, wartosc);
                            break;

                        case 4:
                            KorekcjaGamma(output, obrazek, x, y, wartosc);
                            break;

                        default:
                            fprintf(stderr, "Nie wybrano odpowiedniej opcji");
                    }
                    break;

                case P3:
                    if (wybor == 5)
                    {
                        KonwersjaNaSzarosc(output, obrazek, x, y);
                    }
                    break;
            }
        }
    }
}

void WypiszObrazekNaWyjscie(Obrazek *obrazek, FILE *output)
{
    /* W zaleznosci od typu obrazka wypisz odpowiedni naglowek */
    switch (obrazek->Typ)
    {
        case P2: /* Obrazek w skali szarosci */
            fprintf(output, "P2\n");
            break;

        case P3: /* Obrazek kolorowy RGB */
            fprintf(output, "P3\n");
            break;
    }

    /* Wypisz wymiary obrazka oraz maksymalna skale koloru */
    fprintf(output, "%d ", obrazek->WymX);
    fprintf(output, "%d\n", obrazek->WymY);
    fprintf(output, "%hhu\n\n", obrazek->Skala);

    /* Przejdz po wszystkich elementach tablicy przechowujacej wartosci pikseli */
    for (int y = 0; y < obrazek->WymY; ++y)
    {
        for (int x = 0; x < obrazek->WymX; ++x)
        {
            /* Sprawdz typ obrazka(gdzie sa przechowywane wartosci pikseli) */
            switch (obrazek->Typ)
            {
                case P2:
                    /* Wypisz wartosc piksela w skali szarosci */
                    fprintf(output, "%hhu\t", (obrazek->Piksele[y][x].Szary));
                    break;

                case P3:
                    /* Wypisz wartosci pikseli (czerwony, zielony, niebieski) */
                    fprintf(output, "%hhu\t", (obrazek->Piksele[y][x].Rgb.Red));
                    fprintf(output, "%hhu\t", (obrazek->Piksele[y][x].Rgb.Green));
                    fprintf(output, "%hhu\t", (obrazek->Piksele[y][x].Rgb.Blue));
                    break;
            }
        }
        fprintf(output, "\n");
    }
}

/*  [OUT] obrazek - stryktura przechowujaca informacje o otwartym obrazku P2/P3 takie jak:
 *      - dwuwymiarowa tablica zawierajaca wartosci danego piksela w skali szarosci/RGB
 *      - szerokosc i wysokosc obrazka
 *      - maksymalna wartosc danego piksela w skali szarosci/RGB
 *  [IN] input - podany przez uzytkownika plik(obrazek P2/P3) ktory ma zostac wczytany i przetworzony*/
bool ObrazekWczytaj(Obrazek *obrazek, FILE *input)
{
    {
        /* Zmienna przechowujaca typ obrazka */
        char type[3];

        /* Wczytaj magiczna liczbe */
        if (!fscanf(input, "%2s", type)) {
            puts("Nie mozna wczytaj magicznej liczby z pliku");
            exit(1);
        }

        /* Ustaw typ obrazka na wczytana z pliku liczbe magiczna */
        if (!strcmp("P2", type))
        {
            obrazek->Typ = P2;
        }
        else if(!strcmp("P3", type))
        {
            obrazek->Typ = P3;
        }
        else
        {
            puts("Nie rozpoznano typu");
            exit(1);
        }
    }

    // Wczytaj szerokosc obrazka
    if (!fscanf(input, "%du", &obrazek->WymX))
    {
        puts("Nie mozna wczytac dlugosci pliku");
        exit(1);
    }

    // Wczytaj wysokosc obrazka
    if (!fscanf(input, "%du", &obrazek->WymY))
    {
        puts("Nie mozna wczytaj wysokosci pliku");
        exit(1);
    }

    // Wczytaj skale koloru obrazka
    PominiecieKomentarzy(input);
    if (!fscanf(input, "%hhu", &obrazek->Skala))
    {
        puts("Nie mozna wczytaj skali");
        exit(1);
    }

    /* Zainicjalizuj pierwszy wymiar dynamicznej tablicy dwuwymiarowej */
    obrazek->Piksele = (Piksel **) malloc(sizeof(Piksel *) * obrazek->WymY);
    for (unsigned int y = 0; y < obrazek->WymY; ++y)
    {
        /* Zainicjalinuj drugi wymiar dynamicznej tablicy dwuwymiarowej */
        obrazek->Piksele[y] = (Piksel *) malloc(sizeof(Piksel) * obrazek->WymX);
        for (unsigned int x = 0; x < obrazek->WymX; ++x)
        {
            /* W zaleznosci od typu obrazka wykonaj odpowiednia funkcje wczytania wartosci pikseli do obrazka */
              switch (obrazek->Typ)
              {
                  case P2: /* Obrazek w szkali szarosci*/
                      if(!WczytajSzaryPiksel(input, &obrazek->Piksele[y][x]))
                      {
                          puts("Blad wczytywania piksela");
                          exit(1);
                      }
                      break;

                  case P3: /* Obrazek kolorowy RGB */
                      if(!WczytajRgbPiksel(input, &obrazek->Piksele[y][x]))
                      {
                          puts("Blad wczytywania piksela");
                          exit(1);
                      }
                      break;
              }
        }
    }
}
