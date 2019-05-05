#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "functions.h"
#include "mergesort.h"
#include "readfile.h"
#include "structures.h"


#define size 30
//#include "mergesort.h"
// cd "d:\Desktop\Code\projekt\" ; cd "d:\Desktop\Code\projekt\" ; if ($?) { gcc
// main.c mergesort.c readfile.c functions.c -o main } ; if ($?) { .\main }

list* input(char *input, list *head) {

  if (strcmp(input, "Add\n") == 0) {
    head = add_book(head);
  } else if (strcmp(input, "Check\n") == 0) {
    int check = 0;
    char nazwa[size] = "";
    printf("Podaj nazwe do sprawdzenia:\n");
    fgets(nazwa, size, stdin);
    check = check_unique_name(strtok(nazwa, "\n"), head);
    if (check == 0) {
      printf("%s", "Brak podobnych rekordow\n");
    }
  } else if (strcmp(input, "Edit\n") == 0) {
    char idc[size] = "";

    while (atoi(idc) <= 0) {
      printf("Podaj id do zedytowania:\n");
      fgets(idc, size, stdin);
    }

    int id = atoi(idc);
    if (get_book(head, id)) // sprawdzenie czy element istnieje w liscie
    {
      book xd = *get_book(head, id);
      printf("Nazwa: %s\nAutor: %s\nRok: %i \nGatunek: %s\nId: %i\n", xd.title,
             xd.author, xd.year, xd.subject, xd.book_id);
      edit_book(head, id);
    } else {
      printf("Nie znaleziono ksiazki z takim id");
    }
  } else if (strcmp(input, "Save\n") == 0) {
    char first[size] = "";

    while (atoi(first) < 1 || atoi(first) > 5) {
      printf("Podaj pierwsze miejsce przy zapisie i sortowaniu (1-tytul, "
             "2-autor, 3-rok, 4-gatunek, 5-id)\n");
      fgets(first, size, stdin);
    }
    while (1) {
      char file_name[size] = "";
      printf("Podaj nazwe pliku do jakiego chcesz zapisac wraz z rozszerzeniem "
             "(.txt/.json):\n");
      fgets(file_name, size, stdin);
      strtok(file_name, "\n");
      char *dot = strrchr(file_name, '.'); // szuka ostatniej .
      if (dot &&
          !strcmp(dot,
                  ".txt")) // sprawdza czy istnieje kropka i po kropce wystepuje
      {
        MergeSort(&head, atoi(first));
        save_to_txt(head, file_name, atoi(first));
        break;
      } else if (dot && !strcmp(dot, ".json")) // sprawdza czy istnieje kropka i
                                               // po kropce wystepuje
      {
        MergeSort(&head, atoi(first));
        save_to_json(head, file_name, atoi(first));
        break;
      } else {
        printf("Niepoprawne rozszerzenie pliku\n");
      }
    }
  } else if (strcmp(input, "Sort\n") == 0) {
    while (1) {
      printf("Wedlug czego chcesz sortowac: Tytul-1, Autor-2, Rok-3, "
             "Gatunek-4, Id-5\n");
      char sort[size] = "";
      fgets(sort, size, stdin);
      if (atoi(sort) > 0 && atoi(sort) <= 5) {
        MergeSort(&head, atoi(sort));
        print_all_books(head);
        break;
      }
    }
  } else if (strcmp(input, "Stat\n") == 0) {
    printf("Ksiazek w bazie: %i\n", count_books(head));
    MergeSort(&head, 3);
    count_year_occurence(head);
    MergeSort(&head, 2);
    count_author_occurence(head);
    MergeSort(&head, 4);
    count_subject_occurence(head);
    MergeSort(&head, 5);
  } else if (strcmp(input, "Del\n") == 0) {
    char delinput[size] = "";

    while (atoi(delinput) <= 0) {
      printf("Podaj id do usuniecia:\n");
      fgets(delinput, size, stdin);
    }

    head = delete_list(head, atoi(delinput));
  } else if (strcmp(input, "PrintAll\n") == 0)
    print_all_books(head);

  else if (strcmp(input, "Find\n") == 0) {
    char idp[size] = "";
    char idk[size] = "";
    while (atoi(idp) <= 0) {
      printf("Podaj poczatek przedzialu id pliku do znalezienia:\n");
      fgets(idp, size, stdin);
    }

    while (atoi(idk) <= 0) {
      printf("Podaj koniec przedzialu id pliku do znalezienia:\n");
      fgets(idk, size, stdin);
    }

    int idpi = atoi(idp);
    int idki = atoi(idk);

    if (idpi > idki) {
      int swap = idpi;
      idpi = idki;
      idpi = swap;
      printf("Zamieniono przedzialy id\n");
    }

    char yearp[size] = "";
    char yeark[size] = "";
    while (atoi(yearp) <= 0) {
      printf("Podaj poczatek przedzialu lat pliku do znalezienia:\n");
      fgets(yearp, size, stdin);
    }

    while (atoi(yeark) <= 0) {
      printf("Podaj koniec przedzialu lat pliku do znalezienia:\n");
      fgets(yeark, size, stdin);
    }

    int yearpi = atoi(yearp);
    int yearki = atoi(yeark);

    if (yearpi > yearki) {
      int swap = yearpi;
      yearpi = yearki;
      yearpi = swap;
      printf("Zamieniono przedzialy\n");
    }

    char autor[size] = "";
    printf("Imie/nazwisko lub ich fragenty dla szukanego autora (- brak)\n");
    fgets(autor, size, stdin);

    char tytul[size] = "";
    printf("Nazwa lub jej fragenty dla szukanej ksiazki (-brak)\n");
    fgets(tytul, size, stdin);

    find_print_books(head, idpi, idki, yearpi, yearki, strtok(autor, "\n"),
                     strtok(tytul, "\n"));
  } else if (strcmp(input, "Help\n") == 0) {
    printf("Lista polecen: Eqit-wylacz, Add-dodaj rekord, Check-sprawdzanie "
           "czy rekord istnieje, Stat-wyswietlenie danych statystycznych, "
           "Sort-sortowanie, Save-zapisz do pliku, Del-usun konkretny, "
           "Find-znajdz konkretne, PrintAll-wypisz wszystkie, Help-lista "
           "polecen\n");
  } else if (strcmp(input, "Eqit\n") == 0) {
    printf("Eqiting\n");
    head= delete_whole_list(head);
  }

  else
    printf("Twoje polecenie jest inwalida\n");

  return head;
}
