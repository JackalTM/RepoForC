#include "MergeSort.h"
#ifdef _MERGE_SORT_H

// function to sort the subsection pArray[i .. j] of the array pArray[]
/******************************************************************************************************
 * @name        MergeSortINT_v1
 * @brief       Merge sort version 1
 * 
 * @param[in]   pArray Pointer to an array to sort
 * @param[in]   pArrayTemp Pointer to an array to sort
 * @param[in]   idxStart Index of first element
 * @param[in]   idxEnd Index of last element
 * 
 * @note        void 
 * @return      void 
*/
void MergeSortINT_v1(int pArray[], int pArrayTemp[], int idxStart, int idxEnd, int* pSelfCall)
{
    // the subsection is empty or single element
    if (idxEnd <= idxStart) { return; }

    int idxMid = (idxStart + idxEnd) / 2;
    
    // left sub-array is pArray[i .. mid]
    // right sub-array is pArray[mid + 1 .. j]
    
    MergeSortINT_v1(pArray, pArrayTemp, idxStart, idxMid, pSelfCall);      // sort the left sub-array recursively
    MergeSortINT_v1(pArray, pArrayTemp, idxMid + 1, idxEnd, pSelfCall);    // sort the right sub-array recursively

    int idxleft  = idxStart;      // idxleft points to the beginning of the left sub-array
    int idxright = idxMid + 1;   // idxright points to the beginning of the right sub-array
    int i;      // i is the loop counter

    // we loop from idxStart to idxEnd to fill each element of the final merged array
    for (i = idxStart; i <= idxEnd; i++) 
    {
        if (idxleft == idxMid + 1) 
        {// left pointer has reached the limit
            pArrayTemp[i] = pArray[idxright];
            idxright++;
        } 
        else if(idxright == (idxEnd + 1)) 
        {// right pointer has reached the limit
            pArrayTemp[i] = pArray[idxleft];
            idxleft++;
        } 
        else if(pArray[idxleft] < pArray[idxright]) 
        {// pointer left points to smaller element
            pArrayTemp[i] = pArray[idxleft];
            idxleft++;
        } 
        else // (pArray[idxleft] < pArray[idxright]) 
        {// pointer right points to smaller element
            pArrayTemp[i] = pArray[idxright];
            idxright++;
        }
    }

    for (i=idxStart; i<=idxEnd; i++) 
    {// copy the elements from pArrayTemp[] to pArray[]
        pArray[i] = pArrayTemp[i];
    }
}
//=====================================================================================================

/******************************************************************************************************
 * @name        AssignArrayWithRandom
 * @brief       Asign array with random numbers
 * 
 * @param[in]   max Maximun random number
 * @param[in]   n Amount of elements in array
 * @param[in]   pArray Pointer to an array
 * 
 * @note        void 
 * @return      void 
*/
void AssignArrayWithRandom(int max, int n, int* pArray)
{
    uint8_t i;
    time_t tTime;
/* Intializes random number generator */
    srand((unsigned) time(&tTime));
    for(i=0; i<n; i++)  
    {   pArray[i] = rand() % max;}
}
//=====================================================================================================

void CallMergeSortINT_v1(void) 
{
    int pArr[LIST_MAX_ELEMENT];
    int pArray1[LIST_MAX_ELEMENT] = {9,8,7,6,5,4,3,2,1};
    int pArray2[LIST_MAX_ELEMENT] = {9,6,3,8,5,2,7,4,1};
    int pArray3[LIST_MAX_ELEMENT] = {1,2,3,4,5,6,7,8,9};
    int pArrayTemp[LIST_MAX_ELEMENT];
    int idxFirst, idxLast, i;
    int selfCall;

    AssignArrayWithRandom(10, LIST_MAX_ELEMENT, pArr);
    //for(i=0; i<LIST_MAX_ELEMENT; i++)   {pArr[i] = LIST_MAX_ELEMENT-i;}

    idxFirst = 0x00;
    idxLast  = (sizeof(pArr) /  sizeof(pArr[0])) - 0x01;
    selfCall = 0x00;

#ifdef PRINT_LIST
    printf("Before merge sort: ");
    for(i=0; i<=idxLast; i++)   
    {   putchar(pArr[i] + 0x30); putchar(' ');}
    printf("\n");
#endif

    MergeSortINT_v1(pArr, pArrayTemp, idxFirst, idxLast, &selfCall);

#ifdef PRINT_LIST
    printf(" After merge sort: ");
    for(i=0; i<=idxLast; i++)   
    {   putchar(pArr[i] + 0x30); putchar(' ');}
#endif
    printf("\n Amount of self call %d \n", selfCall+1);
    printf("\n Amount of memory consumed: %dB \n", selfCall+sizeof(int));
}

#endif // _MERGE_SORT_H