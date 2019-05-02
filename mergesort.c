#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "mergesort.h"
#include "structures.h"

// sortuje liste zmieniajac wskazniki(next)
void MergeSort(list **headRef, int num) {
  list *head = *headRef;
  list *a;
  list *b;

  // Rozmiar 0 lub 1
  if ((head == NULL) || (head->next == NULL)) {
    return;
  }

  // Dzieli heada na podlisty a i b
  FrontBackSplit(head, &a, &b);

  // Rekursywnie sortuje podlisty
  MergeSort(&a, num);
  MergeSort(&b, num);

  // laczy podlisty w jedna liste
  *headRef = SortedMerge(a, b, num);
}

list *SortedMerge(list *a, list *b, int num) {
  list *result = NULL;

  // sprawdza czy podlisty nie sa puste
  if (a == NULL)
    return (b);
  else if (b == NULL)
    return (a);

  // wybiera a lub b i sortuje zaleznie od parametru num
  if (num == 1) {
    // if (a->b->title <= b->b->title)
    if (strcmp(a->b->title, b->b->title) <= 0) {
      result = a;
      result->next = SortedMerge(a->next, b, num);
    } else {
      result = b;
      result->next = SortedMerge(a, b->next, num);
    }
    return (result);
  } else if (num == 2) {
    if (strcmp(a->b->author, b->b->author) <= 0) {
      result = a;
      result->next = SortedMerge(a->next, b, num);
    } else {
      result = b;
      result->next = SortedMerge(a, b->next, num);
    }
    return (result);
  } else if (num == 3) {
    if (a->b->year <= b->b->year) {
      result = a;
      result->next = SortedMerge(a->next, b, num);
    } else {
      result = b;
      result->next = SortedMerge(a, b->next, num);
    }
    return (result);
  } else if (num == 4) {
    if (strcmp(a->b->subject, b->b->subject) <= 0) {
      result = a;
      result->next = SortedMerge(a->next, b, num);
    } else {
      result = b;
      result->next = SortedMerge(a, b->next, num);
    }
    return (result);
  } else if (num == 5) {
    if (a->b->book_id <= b->b->book_id) {
      result = a;
      result->next = SortedMerge(a->next, b, num);
    } else {
      result = b;
      result->next = SortedMerge(a, b->next, num);
    }
    return (result);
  }
}

/* Dzieli lista na przednia i tylnia czesc,
    zwraca dwie listy przy pomocy referencji.
    Jezeli rozmiar listy jest nieparzysty, dodatkowy node trafi do przedniej
   listy. fast/slow pointer strategy
    */

void FrontBackSplit(list *source, list **frontRef, list **backRef) {
  list *fast;
  list *slow;
  slow = source;
  fast = source->next;

  /* Bierze dwie "fast" nody i jedna "slow" node*/
  while (fast != NULL) {
    fast = fast->next;
    if (fast != NULL) {
      slow = slow->next;
      fast = fast->next;
    }
  }
  // Jezeli "slow" jest przed srodkiem listy, podziel ja na dwie w tym miejscu

  *frontRef = source;
  *backRef = slow->next;
  slow->next = NULL;
}
