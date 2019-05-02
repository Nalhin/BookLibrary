#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "mergesort.h"
#include "structures.h"


#define size 30

int check_similarity(
    const char *s,
    const char *t) // algorytm Levenshtein'a do sprawdzania podobienstwa
{
  int ls = strlen(s), lt = strlen(t);
  int d[ls + 1][lt + 1];

  for (int i = 0; i <= ls; i++)
    for (int j = 0; j <= lt; j++)
      d[i][j] = -1;

  int dist(int i, int j) {
    if (d[i][j] >= 0)
      return d[i][j];

    int x;
    if (i == ls)
      x = lt - j;
    else if (j == lt)
      x = ls - i;
    else if (s[i] == t[j])
      x = dist(i + 1, j + 1);
    else {
      x = dist(i + 1, j + 1);

      int y;
      if ((y = dist(i, j + 1)) < x)
        x = y;
      if ((y = dist(i + 1, j)) < x)
        x = y;
      x++;
    }
    return d[i][j] = x;
  }
  return dist(0, 0); // zwraca ilosc operacji jaka trzeba wykonac zeby string s
                     // doprowadzic do stringa l
}

int check_unique_name(
    char *name,
    list *head) // sprawdza unikatowosc tytulu (0 unikatowy, 1 podobny)
{

  while (head != NULL) {
    // printf("%i",check_similarity(head->b->title,name));
    // check_similarity(head->b->author,name);
    if (check_similarity(head->b->title, name) < 3 &&
        strlen(name) > 5) // szukana wartosc
    {

      printf("Podobny rekord z id %i z tytulem %s\n", head->b->book_id,
             head->b->title);
      return 1;
    } else if (check_similarity(head->b->title, name) <= 1 &&
               strlen(name) > 3) // szukana wartosc
    {
      printf("Podobny rekord z id %i z tytulem %s\n", head->b->book_id,
             head->b->title);
      return 1;
    }
    head = head->next;
  }

  // printf("Unikatowy rekord\n");
  return 0;
}

int check_unique_id(int id, list *head) // sprawdza unikatowosc id
{

  while (head != NULL) {

    if (head->b->book_id == id) // szukana wartosc
    {

      printf("Juz istnieje rekord z id %i z tytulem %s\n", head->b->book_id,
             head->b->title);
      return 1;
    }

    head = head->next;
  }

  // printf("Unikatowe id\n");
  return 0;
}

int check_unique_id_silent(int id, list *head) // sprawdza unikatowosc id
{

  while (head != NULL) {

    if (head->b->book_id == id) // szukana wartosc
    {

      return 1;
    }

    head = head->next;
  }

  // printf("Unikatowe id\n");
  return 0;
}

book *create_book(char *title, char *author, int year, char *subject,
                  int book_id) // tworzenie ksiazki do struktury
{
  book *b = malloc(sizeof(book)); // book *b = malloc(sizeof(struct book));
  b->title = strdup(title);
  b->author = strdup(author);
  b->year = year;
  b->subject = strdup(subject);
  b->book_id = book_id;
  printf("ID:%i wczytana\n", book_id);
  return b;
}

void print_all_books(list *head) // wypisanie ksiazek
{
  while (head != NULL) {
    printf("\nNazwa: %s\nAutor: %s\nRok: %i \nGatunek: %s\nId: %i\n",
           head->b->title, head->b->author, head->b->year, head->b->subject,
           head->b->book_id);
    head = head->next;
  }
}

book *get_book(list *books, int book_id) // funkcja przeszukujaca liste
{
  list *l = books;

  while (l != NULL) {
    if (l->b->book_id == book_id) // szukana wartosc
    {
      return l->b;
    }
    l = l->next;
  }

  return NULL;
}

void edit_book(list *head, int id) // funkcja edytujaca element listy
{
  list *books = head;
  char value[size];
  char edit[size] = "";
  printf("Ktore pole chcesz zedytowac:\n");
  fgets(edit, size, stdin);

  if (strcmp(edit, "Nazwa\n") == 0) {
    printf("Podaj nowa nazwe:\n");
    fgets(value, size, stdin);
    while (books != NULL) {
      if (books->b->book_id == id) // szukana wartosc
      {

        books->b->title = strdup(strtok(value, "\n"));
      }
      books = books->next;
    }
  } else if (strcmp(edit, "Autor\n") == 0) {
    printf("Podaj nowego autora:\n");
    fgets(value, size, stdin);
    while (books != NULL) {
      if (books->b->book_id == id) // szukana wartosc
      {
        books->b->author = strdup(strtok(value, "\n"));
      }
      books = books->next;
    }
  } else if (strcmp(edit, "Rok\n") == 0) {
    printf("Podaj nowy rok:\n");
    fgets(value, size, stdin);

    while (books != NULL) {
      if (books->b->book_id == id) // szukana wartosc
      {
        books->b->year = atoi(value);
      }
      books = books->next;
    }
  } else if (strcmp(edit, "Gatunek\n") == 0) {
    printf("Podaj nowy gatunek:\n");
    fgets(value, size, stdin);
    while (books != NULL) {
      if (books->b->book_id == id) // szukana wartosc
      {
        books->b->subject = strdup(strtok(value, "\n"));
      }
      books = books->next;
    }
  } else {
    printf("Nie ma takiego pola\n");
  }
  printf("Edycja zakonczona\n");

  // return books;
}

void count_year_occurence(
    list *head) // liczy ile razy dany rok wystepuje w liscie
{
  // head=list_sort_by_year(head);

  list *heads = head;
  int year;

  // sortowanie wedlug roku
  while (heads != NULL) {
    if (heads->b->year == year) {
      heads =
          heads->next; // jezeli taki sam jak poprzedni to nie licz jeszcze raz
      continue;
    }
    year = heads->b->year;
    int count = 0;

    list *l = head;
    while (l != NULL) {
      if (l->b->year == year) // szukana wartosc
      {
        count += 1;
      }
      l = l->next;
    }

    printf("Wystepowanie roku %i - %i razy\n", heads->b->year, count);
    heads = heads->next;
  }
}

void count_author_occurence(list *head) // liczy ile ksiazek napisal dany autor
{

  list *heads = head;
  char author[size] = "";

  while (heads != NULL) {
    if (strcmp(heads->b->author, author) == 0) {
      heads = heads->next;
      continue;
    }

    strncpy(author, heads->b->author, size);
    int count = 0;

    list *l = head;
    while (l != NULL) {
      if (strcmp(l->b->author, author) == 0) // szukana wartosc
      {
        count += 1;
      }
      l = l->next;
    }

    printf("Wystepowanie autora %s - %i razy\n", heads->b->author, count);
    heads = heads->next;
  }
}

void count_subject_occurence(
    list *head) // liczy ile razy wystepuje dany gatunek
{

  list *heads = head;
  char subject[size] = "";

  while (heads != NULL) {
    if (strcmp(heads->b->subject, subject) == 0) {
      heads = heads->next;
      continue;
    }
    // author = heads->b->author;
    strncpy(subject, heads->b->subject, size);
    int count = 0;

    list *l = head;
    while (l != NULL) {
      if (strcmp(l->b->subject, subject) == 0) // szukana wartosc
      {
        count += 1;
      }
      l = l->next;
    }

    printf("Wystepowanie gatunku %s - %i razy\n", heads->b->subject, count);
    heads = heads->next;
  }
}

int count_books(list *head) // liczy ilosc elementow w liscie
{
  // head=list_sort_by_year(head);
  int count = 0;
  while (head != NULL) {

    count += 1;

    head = head->next;
  }

  return count;
}

char *
remove_extra_white_chars(char *temp) // usuwanie dodatkowych bialych znakow
{
  char temp1[size];
  int j = 0;
  bool white = true;
  for (int i = 0; i < size; i++) {
    if (isspace(temp[i]) == 0) {
      temp1[j] = temp[i];
      white = false;

      j++;
    } else if (white == false) {
      temp1[j] = temp[i];
      j++;
      white = true;
    }
  }

  strncpy(temp, temp1, size); // do poprawy
  return temp;
}

char *remove_all_white_chars(char *temp) // usuwanie dodatkowych bialych znakow
{
  char temp1[size];
  int j = 0;

  for (int i = 0; i < size; i++) {
    if (isspace(temp[i]) == 0) {
      temp1[j] = temp[i];

      j++;
    }
  }

  strncpy(temp, temp1, size); // do poprawy
  return temp;
}

list *delete_list(list *currP, int book_id) // usuwa element z listy
{
  if (currP == NULL)
    return NULL;

  if (currP->b->book_id == book_id) {
    list *tempNextP;

    tempNextP = currP->next;

    /* Dealokacja noda */
    free(currP);
    printf("Usunieto %i element\n", book_id);

    return tempNextP;
  }

  currP->next = delete_list(currP->next, book_id);

  return currP;
}

list *
add_book(list *head) // dodaje ksiazke do listy + sprawdzanie poprawnosci danych
{

  char title[size] = "1";
  char author[size] = "1";
  char year[size] = "";
  char subject[size] = "1";
  char id[size] = "";
  int check_title = 1;
  int check_id = 1;
  int p = 1;
  while (check_title == 1 ||
         atoi(title) != 0) // sprawdzanie unikatowosci imienia
  {
    printf("Podaj tytul:\n");
    fgets(title, size, stdin);
    check_title = check_unique_name(strtok(title, "\n"), head);
  }

  while (atoi(author) != 0) {
    printf("Podaj autora:\n");
    fgets(author, size, stdin);
  }
  while (atoi(year) < 999 || atoi(year) > 2030) {
    printf("Podaj rok:\n");
    fgets(year, size, stdin);
  }
  while (atoi(subject) != 0) {
    printf("Podaj gatunek:\n");
    fgets(subject, size, stdin);
  }
  while (check_id == 1 || atoi(id) <= 0) // sprawdzanie unikatowosci id
  {
    printf("Podaj id");

    while (check_unique_id_silent(p, head)) {
      p++;
    }
    printf("(propronowane to %i):\n", p);
    fgets(id, size, stdin);
    if (atoi(id) > 0)
      check_id = check_unique_id(atoi(id), head);
  }

  list *temps = (list *)malloc(sizeof(struct list));
  temps->b = create_book(strtok(title, "\n"), strtok(author, "\n"), atoi(year),
                         strtok(subject, "\n"),
                         atoi(id)); // strtok(subject,"\n") remove new line
  temps->next = head;
  head = temps;
  return head;
}
void find_print_books(list *head, int idpi, int idki, int yearpi, int yearki,
                      char *autor, char *tytul) {
  while (head != NULL) { // printf("%s",autor);
    if ((strcmp(tytul, "-") == 0) && (strcmp(autor, "-") == 0)) {
      char *aut;
      // aut= strstr(head->b->author, autor);
      aut = strstr(head->b->title, autor);
      char *tit;
      tit = strstr(head->b->title, tytul);

      if ((head->b->book_id >= idpi && head->b->book_id <= idki) &&
          (head->b->year >= yearpi && head->b->year <= yearki) && aut && tit) {
        printf("\nNazwa: %s\nAutor: %s\nRok: %i \nGatunek: %s\nId: %i\n",
               head->b->title, head->b->author, head->b->year, head->b->subject,
               head->b->book_id);
      }
    } else if (strcmp(autor, "-") == 1) {
      char *aut;
      // aut= strstr(head->b->author, autor);
      aut = strstr(head->b->author, autor);

      if ((head->b->book_id >= idpi && head->b->book_id <= idki) &&
          (head->b->year >= yearpi && head->b->year <= yearki) && aut) {
        printf("\nNazwa: %s\nAutor: %s\nRok: %i \nGatunek: %s\nId: %i\n",
               head->b->title, head->b->author, head->b->year, head->b->subject,
               head->b->book_id);
      }
    } else if (strcmp(tytul, "-") == 1) {

      char *tit;
      tit = strstr(head->b->title, tytul);

      if ((head->b->book_id >= idpi && head->b->book_id <= idki) &&
          (head->b->year >= yearpi && head->b->year <= yearki) && tit) {
        printf("\nNazwa: %s\nAutor: %s\nRok: %i \nGatunek: %s\nId: %i\n",
               head->b->title, head->b->author, head->b->year, head->b->subject,
               head->b->book_id);
      }
    } else {

      if ((head->b->book_id >= idpi && head->b->book_id <= idki) &&
          (head->b->year >= yearpi && head->b->year <= yearki)) {
        printf("\nNazwa: %s\nAutor: %s\nRok: %i \nGatunek: %s\nId: %i\n",
               head->b->title, head->b->author, head->b->year, head->b->subject,
               head->b->book_id);
      }
    }
    head = head->next;
  }
}

void save_to_txt(list *head, char *file_name, int num) // zapis do pliku txt
{

  FILE *s = fopen(file_name, "w"); // zapis do plika

  if (num == 1) {
    while (head != NULL) {

      fprintf(s, "%s\n%s\n%i\n%s\n%i", head->b->title, head->b->author,
              head->b->year, head->b->subject, head->b->book_id);

      head = head->next;
      if (head != NULL)
        fprintf(s, "\n\n");
    }
    printf("Zapisano do txt\n");
    fclose(s);
  } else if (num == 2) {
    while (head != NULL) {

      fprintf(s, "%s\n%s\n%i\n%s\n%i", head->b->author, head->b->title,
              head->b->year, head->b->subject, head->b->book_id);

      head = head->next;
      if (head != NULL)
        fprintf(s, "\n\n");
    }
    printf("Zapisano do txt\n");
    fclose(s);
  } else if (num == 3) {
    while (head != NULL) {

      fprintf(s, "%i\n%s\n%s\n%s\n%i", head->b->year, head->b->title,
              head->b->author, head->b->subject, head->b->book_id);

      head = head->next;
      if (head != NULL)
        fprintf(s, "\n\n");
    }
    printf("Zapisano do txt\n");
    fclose(s);
  } else if (num == 4) {
    while (head != NULL) {

      fprintf(s, "%s\n%s\n%i\n%s\n%i", head->b->subject, head->b->title,
              head->b->author, head->b->year, head->b->book_id);

      head = head->next;
      if (head != NULL)
        fprintf(s, "\n\n");
    }
    printf("Zapisano do txt\n");
    fclose(s);
  } else if (num == 5) {
    while (head != NULL) {

      fprintf(s, "%i\n%s\n%s\n%i\n%s", head->b->book_id, head->b->title,
              head->b->author, head->b->year, head->b->subject);

      head = head->next;
      if (head != NULL)
        fprintf(s, "\n\n");
    }
    printf("Zapisano do txt\n");
    fclose(s);
  }
}

void save_to_json(
    list *head, char *file_name,
    int num) // funkcja odpowiadajaca za zapis do pliku w formacie json
{

  FILE *s = fopen(file_name, "w"); // zapis do plika

  fprintf(s, "{\"Books\":[");
  if (num == 1) {
    while (head != NULL) {
      fprintf(s, "{");
      fprintf(s,
              "\"Title\": \"%s\",\"Author\": \"%s\",\"Year\": "
              "\"%i\",\"Subject\": \"%s\",\"Book_Id\": \"%i\"}",
              head->b->title, head->b->author, head->b->year, head->b->subject,
              head->b->book_id);

      head = head->next;
      if (head != NULL) {
        fprintf(s, ",");
      }
    }
  }
  if (num == 2) {
    while (head != NULL) {
      fprintf(s, "{");
      fprintf(s,
              "\"Author\": \"%s\",\"Title\": \"%s\",\"Year\": "
              "\"%i\",\"Subject\": \"%s\",\"Book_Id\": \"%i\"}",
              head->b->author, head->b->title, head->b->year, head->b->subject,
              head->b->book_id);

      head = head->next;
      if (head != NULL) {
        fprintf(s, ",");
      }
    }
  }
  if (num == 3) {
    while (head != NULL) {
      fprintf(s, "{");
      fprintf(s,
              "\"Year\": \"%i\",\"Title\": \"%s\",\"Author\": "
              "\"%s\",\"Subject\": \"%s\",\"Book_Id\": \"%i\"}",
              head->b->year, head->b->title, head->b->author, head->b->subject,
              head->b->book_id);

      head = head->next;
      if (head != NULL) {
        fprintf(s, ",");
      }
    }
  }
  if (num == 4) {
    while (head != NULL) {
      fprintf(s, "{");
      fprintf(s,
              "\"Subject\": \"%s\",\"Title\": \"%s\",\"Author\": "
              "\"%s\",\"Year\": \"%i\",\"Book_Id\": \"%i\"}",
              head->b->subject, head->b->title, head->b->author, head->b->year,
              head->b->book_id);

      head = head->next;
      if (head != NULL) {
        fprintf(s, ",");
      }
    }
  }
  if (num == 5) {
    while (head != NULL) {
      fprintf(s, "{");
      fprintf(s,
              "\"Book_Id\": \"%i\",\"Title\": \"%s\",\"Author\": "
              "\"%s\",\"Year\": \"%i\",\"Subject\": \"%s\"}",
              head->b->book_id, head->b->title, head->b->author, head->b->year,
              head->b->subject);

      head = head->next;
      if (head != NULL) {
        fprintf(s, ",");
      }
    }
  }
  fprintf(s, "]}");
  printf("Zapisano do JSON\n");
  fclose(s);
}
