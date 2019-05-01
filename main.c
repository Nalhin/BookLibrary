#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structures.h"
#include "mergesort.h"
#include "readfile.h"
#include "functions.h"
#include "input.h"
#define size 30
//#include "mergesort.h"
//cd "d:\Desktop\Code\projekt\" ; cd "d:\Desktop\Code\projekt\" ; if ($?) { gcc main.c mergesort.c readfile.c functions.c input.c -o main } ; if ($?) { .\main }



int main()
{
    list *head = NULL;
    head = read_parse_file(head);
    char inputs[10] = "";
    printf("=============================================================================================\n");
    printf("Lista polecen: Eqit-wylacz, Add-dodaj rekord, Check-sprawdzanie czy rekord istnieje, Stat-wyswietlenie danych statystycznych, Sort-sortowanie, Save-zapisz do pliku, Del-usun konkretny, Find-znajdz konkretne, PrintAll-wypisz wszystkie, Help-lista polecen\n");

    while (1)
    { 
        fgets(inputs, sizeof inputs, stdin);
        input(inputs, head);
    }

    printf("Dobranoc");
    return 0;
}