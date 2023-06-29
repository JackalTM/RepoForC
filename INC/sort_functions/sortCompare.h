#include <time.h>
#include "MergeSort.h"
#include "QuickSort.h"
#include "BubleSort.h"

#define MAX_ELEMENTS 16 // 0x 3C 0000 B
#define TIME_MULTIPLICATOR 1000
#define AMOUNT_OF_ZEROS 3

#if MAX_ELEMENTS < 64
#define PRINT_ARRAYS
#endif

int* pArrayMerge[MAX_ELEMENTS];
int* pArrayQuick[MAX_ELEMENTS];
int* pArrayBuble[MAX_ELEMENTS];
int* pArrayMergeTemp[MAX_ELEMENTS];

clock_t start, end;
double cpu_time_merge, cpu_time_quick, cpu_time_buble;

void PrintDataForMerge(int* pArrayMerge);
void PrintDataForQuick(int* pArrayQuick);
void PrintDataForBuble(int* pArrayBuble);

void CallTest(void);