    
#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct //definicja struktury ksiazki
{
    char *title;
    char *author;
    int year;
    char *subject;
    int book_id;
} book;

typedef struct list //struktura listy
{
    book *b;
    struct list *next;
} list;

#endif // STRUCTURES_H_INCLUDED