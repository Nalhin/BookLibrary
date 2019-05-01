#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "readfile.h"
#include "structures.h"
#include "functions.h"

#define size 30

list *read_parse_file(list *head)
{ //funkcja odpowiadajaca za wczytanie pliku i zapisanie go w liscie
    FILE *f;
    char *filename = "xd.txt";

    char temp[size];
    int numer = 0; //numer elementu

    // list *books = NULL;           //zdefiniowanie pustej listy
    //  books = malloc(sizeof(book)); //przydzial pamieci na liste

    char title[size] = "";
    char author[size] = "";
    int year;
    char subject[size] = "";
    int id;

    f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Nie mozna otworzyc pliku %s\n", filename);
        exit(1);
    }

    while (fgets(temp, size, f) != NULL)
    {

        for (int i = 0;; i++)
        {

            if (temp[i] == '\0') //nowa linijka
            {
                numer++;
                break;
            }
        }

        if (numer % 6 != 0 && strcmp(temp, "\n") == 0) //eliminacja dodatkowych enterow
        {
            numer--;
            continue;
        }

        else if (numer % 6 != 0 && isspace(temp[0]) != 0) //eliminacja wszystkich bledow z pustymi liniami
        {
            char temp1[size];
            int j = 0;

            for (int i = 1; i < size; i++)
            {
                if (isspace(temp[i]) == 0 || j > 0)
                {
                    temp1[j] = temp[i];
                    j++;
                }
            }

            if (j != 0 && temp1[0] != '\0')
            {
                strncpy(temp, temp1, size);
            }

            else
            {
                numer--;
                continue;
            }
        }

        if (temp[0] >= 97 && temp[0] <= 122)
        {
            temp[0] = toupper(temp[0]);
        }

        switch (numer % 6)
        {
        case 1:
        {
            int check_title = check_unique_name(strtok(temp, "\n"), head);

            while (check_title == 1 || atoi(temp) != 0) //sprawdzanie unikatowosci imienia
            {
                printf("Podaj unikatowy i poprawny tytul:\n");
                fgets(temp, size, stdin);
                check_title = check_unique_name(strtok(temp, "\n"), head);
            }
            strncpy(temp, remove_extra_white_chars(temp), size);
            strncpy(title, temp, size);
        }
        break;
        case 2:
            while (atoi(temp) != 0)
            {
                printf("Podaj poprawnego autora %s\n", title);
                fgets(temp, size, stdin);
            }
            strncpy(temp, remove_extra_white_chars(temp), size);
            strncpy(author, temp, size);

            break;
        case 3:
            strncpy(temp, remove_all_white_chars(temp), size);
            while (atoi(temp) < 999 || atoi(temp) > 2030)
            {
                printf("Podaj poprawny rok dla %s\n", title);
                fgets(temp, size, stdin);
            }
            year = atoi(temp);

            break;
        case 4:
            while (atoi(temp) != 0)
            {
                printf("Podaj poprawnego gatunek %s\n", title);
                fgets(temp, size, stdin);
            }
            strncpy(temp, remove_extra_white_chars(temp), size);
            strncpy(subject, temp, size);

            break;
        case 5:
        {
            strncpy(temp, remove_all_white_chars(temp), size);
            int check_id = check_unique_id(atoi(temp), head);
            int p = 1;
            while (check_id == 1 || atoi(temp) <= 0) //sprawdzanie unikatowosci id
            {
                while (check_unique_id_silent(p, head))
                {
                    p++;
                }
                printf("Podaj poprawne id dla rekordu %s (proponowane %i)\n", title, p);
                fgets(temp, size, stdin);
                if (atoi(temp) > 0)
                    check_id = check_unique_id(atoi(temp), head);
            }

            id = atoi(temp);
            list *temps = (list *)malloc(sizeof(struct list));
            temps->b = create_book(strtok(title, "\n"), strtok(author, "\n"), year, strtok(subject, "\n"), id); //strtok(subject,"\n") remove new line
            temps->next = head;
            head = temps;
            // books->b =create_book(title, author, year, subject, id);
            //  books->next;
            break;
        }
        }

        //   printf("%s", temp);
    }

    fclose(f);
    return head;
}