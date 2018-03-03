#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Wyswietl.h"

#define DL_LINII 1024

/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void Display(char *n_pliku)
{
    char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

    strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
    strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
    strcat(polecenie," &");
    printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
    system(polecenie);             /* wykonanie polecenia        */
}