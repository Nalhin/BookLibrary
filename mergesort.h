#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED

#include "structures.h"

void MergeSort(list **headRef, int num);
list *SortedMerge(list *a, list *b, int num);
void FrontBackSplit(list *source,
                    list **frontRef, list **backRef);


#endif // MERGESORT_H_INCLUDED