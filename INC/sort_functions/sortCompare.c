#include "sortCompare.h"
#ifdef _SORT_COMPARE_H

void PrintDataForMerge(int* pArrayMerge)
{
    int i;
    char tChar;
    putchar('\n');
    printf("pArrayMerge[]:= ");
    for(i=0; i< MAX_ELEMENTS; i++)  
    {
        tChar = (char)(pArrayMerge[i]);
        tChar = tChar + 0x30;
        putchar(tChar);
        putchar(' ');
    }
    putchar('\n');
}
void PrintDataForQuick(int* pArrayQuick)
{
    int i;
    char tChar;
    putchar('\n');
    printf("pArrayQuick[]:= ");
    for(i=0; i< MAX_ELEMENTS; i++)  
    {
        tChar = (char)(pArrayQuick[i]);
        tChar = tChar + 0x30;
        putchar(tChar); 
        putchar(' ');
    }
    putchar('\n');
}
void PrintDataForBuble(int* pArrayBuble)
{
    int i;
    char tChar;
    putchar('\n');
    printf("pArrayBuble[]:= ");
    for(i=0; i< MAX_ELEMENTS; i++)  
    {
        tChar = (char)(pArrayBuble[i]);
        tChar = tChar + 0x30;
        putchar(tChar); 
        putchar(' ');
    }
    putchar('\n');
}

void CallTest(void)
{   int i, selfCallMerge, selfCallQuick, selfCallBuble;
    selfCallMerge = 0;
    selfCallQuick = 0;
    selfCallBuble = 0;

    //AssignArrayWithRandom(10, LIST_MAX_ELEMENT, (int*)pArrayMerge);
    AssignArrayWithRandom(10, LIST_MAX_ELEMENT, (int*)pArrayBuble);
    for(i=0; i<MAX_ELEMENTS; i++)
    {
        pArrayMerge[i] = pArrayBuble[i];
        pArrayQuick[i] = pArrayBuble[i];
    }

#ifdef PRINT_ARRAYS
    PrintDataForMerge((int*)pArrayMerge);
    PrintDataForQuick((int*)pArrayQuick);
    PrintDataForBuble((int*)pArrayBuble);
#endif

    start = clock();
    MergeSortINT_v1((int*)pArrayMerge, (int*)pArrayMergeTemp, 0x00, MAX_ELEMENTS-1, &selfCallMerge);
    end = clock();
    cpu_time_merge = ((double) (end - start)) / CLOCKS_PER_SEC;
    cpu_time_merge = cpu_time_merge * TIME_MULTIPLICATOR;

    start = clock();
    //QuickSort_INT_v1((int*)pArrayQuick, 0x00, MAX_ELEMENTS, &selfCallQuick);
    end = clock();
    cpu_time_quick = ((double) (end - start)) / CLOCKS_PER_SEC;
    cpu_time_quick = cpu_time_quick * TIME_MULTIPLICATOR;

    start = clock();
    SortBubleINT((int*)pArrayBuble, MAX_ELEMENTS, &selfCallBuble);
    end = clock();
    cpu_time_buble = ((double) (end - start)) / CLOCKS_PER_SEC;
    cpu_time_buble = cpu_time_buble * TIME_MULTIPLICATOR;

#ifdef PRINT_ARRAYS
    PrintDataForMerge((int*)pArrayMerge);
    PrintDataForQuick((int*)pArrayQuick);
    PrintDataForBuble((int*)pArrayBuble);
#endif

    printf("Methods compare: \n");
    printf("Time of MergeSort:  %f e-%d \n", cpu_time_merge, AMOUNT_OF_ZEROS);
    printf("Time of QuickSort:  %f e-%d \n", cpu_time_quick, AMOUNT_OF_ZEROS);
    printf("Time of BubleSort:  %f e-%d \n", cpu_time_buble, AMOUNT_OF_ZEROS);
}

#endif // _SORT_COMPARE_H