#include "_sort_function_inc.h"
#ifdef _QUICK_SORT_H

//================================================================================================
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SwapTwoElementsINT (int *pA, int *pB);
int QuickSortPartitionINT (int pArray[], int idxLow, int idxHigh);

void QuickSort_INT_v1(int pArray[], int first, int last, int* pSelfCall);
void QuickSort_INT_v2 (int parray[], int low, int high, int* pSelfCall);

void CallQuickSortINT_v1(int idxArray);
void CallQuickSortINT_v2(int idxArray);
//================================================================================================

#endif // _QUICK_SORT_H