#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIST_MAX_ELEMENT 32
#define PRINT_LIST
void AssignArrayWithRandom(int max, int n, int* pArray);
void MergeSortINT_v1(int pArray[], int pArrayTemp[], int idxStart, int idxEnd, int* pSelfCall);
void CallMergeSortINT_v1(void) ;
