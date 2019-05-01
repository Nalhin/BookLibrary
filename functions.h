#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "structures.h"
#include "mergesort.h"


int check_similarity(const char *s, const char *t);
int check_unique_name(char *name, list *head);
int check_unique_id(int id, list *head);
int check_unique_id_silent(int id, list *head);
book *create_book(char *title, char *author, int year, char *subject, int book_id);
void print_all_books(list *head);
book *get_book(list *books, int book_id);
void edit_book(list *head, int id);
void count_year_occurence(list *head);
void count_author_occurence(list *head);
void count_subject_occurence(list *head);
int count_books(list *head);
char *remove_extra_white_chars(char *temp);
char *remove_all_white_chars(char *temp);
list *delete_list(list *currP, int book_id);
list *add_book(list *head);
void find_print_books(list *head, int idpi, int idki, int yearpi, int yearki, char *autor, char *tytul);
void save_to_txt(list *head, char *file_name, int num);
void save_to_json(list *head, char *file_name, int num);



#endif // FUNCTIONS_H_INCLUDED