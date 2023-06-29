#include "QuickSort.h"

/******************************************************************************************************
 * @name        SwapTwoElementsINT
 * @brief       Quick sort function
 * @param[in]   pA Pointer first element
 * @param[in]   pB Pointer second element
 * @note        void 
 * @return      void 
*/
void SwapTwoElementsINT (int *pA, int *pB)
{
  int temp;
  temp = *pA;
  *pA = *pB;
  *pB = temp;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        QuickSortPartitionINT
 * @brief       Split array into two, on one side of is bigger and on the other side smaller
 * @param[in]   pArray Pointer to an array to sort
 * @param[in]   low Index of first element
 * @param[in]   high Index of last element
 * @note        void 
 * @return      new pivot idx
*/
int QuickSortPartitionINT(int pArray[], int idxLow, int idxHigh)
{
    int i;
    int idxNewPivot, pivotVal;

    pivotVal = pArray[idxHigh];
    idxNewPivot = (idxLow - 1);

    for (i=idxLow; i <= idxHigh - 1; i++)
    {
        if (pArray[i] <= pivotVal)
        {
            idxNewPivot++;
            SwapTwoElementsINT(&pArray[idxNewPivot], &pArray[i]);
        }
    }
    SwapTwoElementsINT(&pArray[idxNewPivot + 1], &pArray[idxHigh]);
    return (idxNewPivot + 1);
}
//=====================================================================================================

/******************************************************************************************************
 * @name        QuickSort_INT_v1
 * @brief       Quick sort function
 * @param[in]   pArray Pointer to an array to sort
 * @param[in]   first Index of first element
 * @param[in]   last Index of last element
 * @note        void 
 * @return      void 
*/
void QuickSort_INT_v1(int pArray[], int first, int last, int* pSelfCall)
{
    uint8_t i, j, pivot, temp;
    if(first < last)
    {
        pivot = first;
        i = first;
        j = last;

        while(i < j)
        {
            while((pArray[i] <= pArray[pivot]) && (i < last)) 
            {   i++;}

            while(pArray[j] > pArray[pivot]) 
            {   j--;}

            if(i < j)
            {
                temp=pArray[i];
                pArray[i]=pArray[j];
                pArray[j]=temp;
            }
        }

        temp=pArray[pivot];
        pArray[pivot]=pArray[j];
        pArray[j]=temp;

        QuickSort_INT_v1(pArray, first,  j - 1, pSelfCall);
        QuickSort_INT_v1(pArray, j + 1,  last, pSelfCall);
    }
}
//=====================================================================================================

/******************************************************************************************************
 * @name        QuickSort_INT_v2
 * @brief       Quick sort version v2
 * @param[in]   pArray Pointer to an array to sort
 * @param[in]   low Index of first element
 * @param[in]   high Index of last element
 * @note        void 
 * @return      void 
*/
void QuickSort_INT_v2 (int parray[], int low, int high, int* pSelfCall)
{
    *pSelfCall = *pSelfCall + 0x01;
    if(high <= low) return;
    
    int idxPivot;
    idxPivot = QuickSortPartitionINT(parray, low, high);

    QuickSort_INT_v2(parray, low, idxPivot - 1, pSelfCall);
    QuickSort_INT_v2(parray, idxPivot + 1, high, pSelfCall);
}
//=====================================================================================================

//=====================================================================================================
void CallQuickSortINT_v1(int idxArray)
{
    int pArray1[] = {1,4,7,2,5,8,3,6,9};
    int pArray2[] = {9,6,3,8,5,2,7,4,1};
    int pArray3[] = {6,5,4,3,2,1,7,8,9};
    int* ppArray[3];
    int idxFirst, idxLast, i;
    int selfCall;

    ppArray[0] = pArray1; ppArray[1] = pArray2; ppArray[2] = pArray3;
    idxFirst = 0x00;
    idxLast  = (sizeof(pArray1) /  sizeof(ppArray[i][0])) - 0x01;
    selfCall = 0x00;

    printf("V2 Before sort: ");
    for(i=0; i<=idxLast; i++)   
    {   putchar(ppArray[idxArray][i] + 0x30);}
    printf("\n");

    QuickSort_INT_v1(ppArray[idxArray], idxFirst, idxLast, &selfCall);

    printf("V2 After sort: ");
    for(i=0; i<=idxLast; i++)   
    {   putchar(ppArray[idxArray][i] + 0x30);}
    printf("\n.\n");
}
void CallQuickSortINT_v2(int idxArray)
{
    int pArray1[] = {9,8,7,6,5,4,3,2,1};
    int pArray2[] = {9,6,3,8,5,2,7,4,1};
    int pArray3[] = {1,2,3,4,5,6,7,8,9};
    int* ppArray[3];
    int idxFirst, idxLast, i;
    int selfCall;

    ppArray[0] = pArray1; ppArray[1] = pArray2; ppArray[2] = pArray3;
    idxFirst = 0x00;
    idxLast  = (sizeof(pArray1) /  sizeof(ppArray[i][0])) - 0x01;
    selfCall = 0x00;

    printf("V2 Before sort: ");
    for(i=0; i<=idxLast; i++)   
    {   putchar(ppArray[idxArray][i] + 0x30);}
    printf("\n");

    QuickSort_INT_v2(ppArray[idxArray], idxFirst, idxLast, &selfCall);

    printf("V2 After sort: ");
    for(i=0; i<=idxLast; i++)   
    {   putchar(ppArray[idxArray][i] + 0x30);}
    printf("\n Amount of self call %d \n . \n", selfCall);  
}
//=====================================================================================================