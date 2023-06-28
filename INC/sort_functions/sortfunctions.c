#include "sortfunctions.h"

/******************************************************************************************************
 * @name        _CheckIfSorted 
 * @brief       This function check is array is sorted and return value
 * 
 * @param[in]   pArray      Pointer to array size of uint8_t
 * @param[in]   inEleN      Number of elements 
 * @param[in]   inAscDsc    Ascending or descending order to sort
 * 
 * @note        static private function
 * 
 * @return      Status of array if sorted or not
*/
static uint8_t _CheckIfSorted(uint8_t* pArray, uint8_t inEleN, uint8_t inAscDsc)
{
    uint8_t i, j; j = 0;
    if(inAscDsc == 0x01)
    {
        for(i=1; i<inEleN; i++)
        {
            if(*(pArray + i - 1) >= *(pArray + i))  
            { j++; }
        }
    }
    else if(inAscDsc == 0xFF)
    {
        for(i=1; i<inEleN; i++)
        {
            if(*(pArray + i - 1) <= *(pArray + i))  
            { j++; }
        }
    }
    if(j == inEleN) return inAscDsc;
    else            return 0x00;
}
//=====================================================================================================

/******************************************************************************************************
 * @name    
 * @brief
 * @param[in]
 * @note
 * @return
*/
uint8_t SortBubleBYTE(uint8_t* pArray, uint8_t inEleN, uint8_t inAscDsc)
{
    uint8_t i,j, nmax, tByte;
    nmax = 0x00;

    if(inAscDsc == 0x01)
    {   do
        {   j = 0x00; nmax++;
            for(i=1; i<inEleN; i++)
            {
                if(*(pArray + i - 1) < *(pArray + i))
                {   j++;
                    tByte = *(pArray + i);
                    *(pArray + i) = *(pArray + i - 1);
                    *(pArray + i - 1) = tByte;
                }
            }
        } while ((j > 0x00) && (nmax < 0xF0));
    }
    else if(inAscDsc == 0xFF)
    {   do
        {   j = 0x00; nmax++;
            for(i=1; i<inEleN; i++)
            {
                if(*(pArray + i - 1) > *(pArray + i))
                {   j++;
                    tByte = *(pArray + i);
                    *(pArray + i) = *(pArray + i - 1);
                    *(pArray + i - 1) = tByte;
                }
            }
        } while ((j > 0x00) && (nmax < 0xF0));
    }
    else
        return 0x00;

    return nmax;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        _CompareElementStr
 * @brief       Static function that copare two strings
 *  
 * @param[in]   pStrA Base pointer to first string
 * @param[in]   pStrB Base pointer to second string
 * 
 * @note        This compare function start from smaler addr
 * @return      Compare resoult: 0x01 0x00 0xFF
*/
static uint8_t _CompareElementStr(char pStrA[], char pStrB[], uint8_t inStrLen)
{
    uint8_t i, cmpResoult; 

    for(i=0; i<inStrLen; i++)
    {
        if(pStrA[i] > pStrB[i])   
        {   cmpResoult = COMPARE_MORE; break;}
        else if(pStrA[i] < pStrB[i]) 
        {   cmpResoult = COMPARE_LESS; break;}
        else
            cmpResoult = COMPARE_EQUAL;
    }
    return cmpResoult;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        _CompareElementANYINT
 * @brief       Static function that compare data from one base poiner to another 
 * 
 * @param[in]   pA Base pointer to first data 
 * @param[in]   pB Base pointer to second data 
 * @param[in]   inTotalSize Data total size
 * 
 * @note        This compare function start from bigger addr
 * @return      Compare resoult: 0x01 0x00 0xFF
*/
static uint8_t _CompareElementANYINT(uint8_t* pA, uint8_t* pB, uint8_t inTotalSize)
{
    uint8_t i, cmpResoult; 
    i = 0;
    pA = pA + inTotalSize - 1;
    pB = pB + inTotalSize - 1;
    while(i < inTotalSize)
    {
        if(*(pA - i) > *(pB - i))   
        {   cmpResoult = COMPARE_MORE; break;}
        else if(*(pA - i) < *(pB - i)) 
        {   cmpResoult = COMPARE_LESS; break;}
        else
            cmpResoult = COMPARE_EQUAL; 
        i++; 
    }
    return cmpResoult;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        _MoveElementANY
 * @brief       Static function that move data from one structure or data types to another byte by byte
 * 
 * @param[in]   pDEST Destination base pointer 
 * @param[in]   pSRC Source base pointer
 * @param[in]   inTotalSize Total size in bytes
 * 
 * @note        void 
 * @return      void 
*/
static void _MoveElementANY(uint8_t* pDEST, uint8_t* pSRC, uint8_t inTotalSize)
{
    uint8_t i;
    for(i=0; i<inTotalSize; i++)
    {
        *(pDEST + i) = *(pSRC + i);
    }
}
//=====================================================================================================

/******************************************************************************************************
 * @name        _MoveStr
 * @brief       Static function that move array of strings to other array
 * 
 * @param[in]   pArrStrDST Pointer to destination arrray
 * @param[in]   pArrStrSRC Pointer to source array
 * @param[in]   inSize Amount of elements is an array
 * 
 * @note
 * @return      void 
*/
static void _MoveStr(char* pArrStrDST, char* pArrStrSRC, uint8_t inAmoutOfElems)
{
    uint8_t i;
    for(i=0; i<inAmoutOfElems; i++)
    {
        pArrStrDST[i] = pArrStrSRC[i];
    }
}
//=====================================================================================================

/******************************************************************************************************
 * @name        SortBubleForAllTypes
 * @brief       Simple buble sort using function pointers
 * 
 * @param[in]   pBasePtr Base pointer to array. Array can be of any type
 * @param[in]   inNumOfEle Number of elements in array
 * @param[in]   inSizeOfEle Size of a array memeber
 * @param[in]   pFunStruct Pointer to structure with funtion pointers to handle demand types
 * 
 * @note        Function to move and compare need to be implement and asign to structure
 * @return      State of sort process
*/
uint8_t SortBubleForAllIntTypes(uint8_t* pBasePtr, uint8_t inNumOfEle, uint8_t inSizeOfEle, sortFunctionPointers_t* pFunStruct)
{
    uint8_t i,j, nmax, temp, i_prev, i_curr; 
    nmax = 0x00; 

    uint8_t* pTemp = (uint8_t*)malloc(inSizeOfEle);

    do
    {   j = 0x00; nmax++;
        for(i=1; i<inNumOfEle; i++)
        {
            i_curr = i * inSizeOfEle;
            i_prev = i_curr - inSizeOfEle;
            
            temp = (*pFunStruct->pCompare)(pBasePtr + i_prev, pBasePtr + i_curr, inSizeOfEle);
            if(temp == pFunStruct->sortOrder)
            {   j++;
                (*pFunStruct->pMove)(pTemp,                 pBasePtr + i_prev,      inSizeOfEle);
                (*pFunStruct->pMove)(pBasePtr + i_prev,     pBasePtr + i_curr,      inSizeOfEle);
                (*pFunStruct->pMove)(pBasePtr + i_curr,     pTemp,                  inSizeOfEle);         
            }
        }
    } while ((j > 0x00) && (nmax < 0xF0));

    free(pTemp);

    return 0x00;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        SortBubleForAllTypes
 * @brief       Simple buble sort using function pointers
 * 
 * @param[in]   pBasePtr Base pointer to array of pointers. Array of strings
 * @param[in]   inNumOfEle Number of elements in array
 * @param[in]   inSizeOfEle Size of a string
 * @param[in]   pFunStruct Pointer to structure with funtion pointers to handle demant types
 * 
 * @note        Function to move and compare need to be implement and asign to structure
 * @return      State of sort process
*/
uint8_t SortBubleForStrArrTypes(char** ppArrStr, uint8_t inArrN, uint8_t inStrLen)
{
    uint8_t i,j, nmax, temp, i_prev, i_curr; 
    char* pStr = (char*)malloc(inStrLen + 1);

    nmax = 0x00; 
    do
    {   j = 0x00; nmax++;
        for(i=1; i<inArrN; i++)
        {
            i_curr = i;
            i_prev = i_curr - 1;

            temp = _CompareElementStr(*(ppArrStr + i_prev), *(ppArrStr + i_curr), inStrLen);
            if(temp == COMPARE_MORE)
            {   
                j++;      
                _MoveStr(pStr, ppArrStr[i_curr], inStrLen);
                _MoveStr(ppArrStr[i_curr], ppArrStr[i_prev], inStrLen);
                _MoveStr(ppArrStr[i_prev], pStr, inStrLen);
            }
        }
    } while ((j > 0x00) && (nmax < 0xF0));
    free(pStr);

    return 0x00;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        CallSortBouble1
 * @brief       Call to test program
 * @param[in]   void 
 * @note        void 
 * @return      void 
*/
void CallSortBouble1(void)
{
    char tChar;
    uint8_t i,n;
    uint8_t byteArray[] = { 56,9,8,74,6,59,4,31,2,1,1,21,14 };

    printf("Before sort: ");
    for(i=0; i< sizeof(byteArray); i++)
    {
        printf(" %2x ", byteArray[i]);
    }

    printf("\n After sort: ");
    n = SortBubleBYTE(byteArray, sizeof(byteArray), 0xFF);
    for(i=0; i< sizeof(byteArray); i++)
    {
        printf(" %2x ", byteArray[i]);
    }
    printf("NUmber of loops %x \n", n);

    printf("\n After sort: ");
    n = SortBubleBYTE(byteArray, sizeof(byteArray), 0x01);
    for(i=0; i< sizeof(byteArray); i++)
    {
        printf(" %2x ", byteArray[i]);
    }
    printf("NUmber of loops %x \n", n);
}
//=====================================================================================================

/******************************************************************************************************
 * @name        CallSortBouble2
 * @brief       Call to test program
 * @param[in]   void 
 * @note        void 
 * @return      void 
*/
void CallSortBouble2(void)
{
    int i, n;
    uint16_t pArr[] = {5,7,3,8,2,1,7};
    uint8_t itemSize = sizeof(pArr[0]);
    uint8_t numOfItems = sizeof(pArr) / itemSize;

    sortFunctionPointers_t tFunStruct;
    tFunStruct.pCompare    = &_CompareElementANYINT;
    tFunStruct.pMove       = &_MoveElementANY;
    //tFunStruct.sortOrder   = COMPARE_MORE;
    tFunStruct.sortOrder   = COMPARE_LESS;

    printf("Before sort: ");
    
    for(i=0; i<numOfItems; i++)
    {
        printf(" %4x,", *(pArr + i));
    }

    SortBubleForAllIntTypes((uint8_t*)(pArr), numOfItems, itemSize, (sortFunctionPointers_t*)&tFunStruct);

    printf("\n After sort: ");
    for(i=0; i<numOfItems; i++)
    {
        printf(" %4x,", pArr[i]);
    }
}
//=====================================================================================================

/******************************************************************************************************
 * @name        CallSortBouble3
 * @brief       Call to test program
 * @param[in]   void 
 * @note        void 
 * @return      void 
*/
void CallSortBouble3(void)
{
    int i, n;
    char pArr[] = {"bca abc cba "};

    uint8_t itemSize = 4;//sizeof(pArr[0]);
    uint8_t numOfItems = 3;//sizeof(pArr) / itemSize;

    sortFunctionPointers_t tFunStruct;
    tFunStruct.pCompare    = &_CompareElementStr;
    tFunStruct.pMove       = &_MoveElementANY;
    tFunStruct.sortOrder   = COMPARE_MORE;
    //tFunStruct.sortOrder   = COMPARE_LESS;

    printf("Before sort: %s \n", pArr);
    SortBubleForAllIntTypes((uint8_t*)(pArr), numOfItems, itemSize, (sortFunctionPointers_t*)&tFunStruct);
    printf(" After sort: %s,", pArr);
}
//=====================================================================================================

/******************************************************************************************************
 * @name        CallSortBouble4
 * @brief       Call to test program
 * @param[in]   void 
 * @note        void 
 * @return      void 
*/
void CallSortBouble4(void)
{
    int i;
    const char* strArr[] = 
    {
    "First entry ",
    "Second entry",
    "Third entry ",
    "123456789ABC"
    };
    char pStr0[] = {"123456789ABC"};
    char pStr1[] = {"First entry "}; 
    char pStr2[] = {"Second entry"}; 
    char pStr3[] = {"Third entry "};
    char pStr4[] = {"123456789ABC"};
    char* ppArr[] = {pStr0, pStr1, pStr2, pStr3, pStr4};

    printf("Before sort: ");
    for(i=0; i<LIST_LENGHT; i++)
    {
        printf(" %s ", *(ppArr + i));
    }

    SortBubleForStrArrTypes((char**)(ppArr), LIST_LENGHT, STRING_LEN);

    printf("\n After sort: "); 
    for(i=0; i<LIST_LENGHT; i++)
    {
        printf(" %s ", *(ppArr + i));
    }
    printf("\n \n");
}
//=====================================================================================================

/******************************************************************************************************
 * @name        CallSortBouble5
 * @brief       Call to test program
 * @param[in]   void 
 * @note        void 
 * @return      void 
*/
void CallSortBouble5(void)
{
    ;
}
//=====================================================================================================

//====================================================================================================================================================

//=====================================================================================================

/******************************************************************************************************
 * @name        _SwapBytesInList
 * @brief       Quick sort function
 * @param[in]   void 
 * @note        void 
 * @return      void 
*/
void static _SwapBytesInList(uint8_t* pBase, uint8_t idxA, uint8_t idxB)
{
    uint8_t temp;
    temp = *(pBase + idxA);
    *(pBase + idxA) = *(pBase + idxB);
    *(pBase + idxB) = temp;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        _SwapBytesInList
 * @brief       Quick sort function
 * @param[in]   void 
 * @note        void 
 * @return      void 
*/
uint8_t static _SplitListByPivot(uint8_t* pBase, uint8_t inSTART, uint8_t inEND, uint8_t i_pivot, uint8_t arrSTART, uint8_t arrEND, uint8_t PrintData)
{
    uint8_t i, j;
    uint8_t tExit, pivotValue;

    printf("\n ixd= %x pivot = %x || \n", i_pivot, pBase[i_pivot]);

    pivotValue = pBase[i_pivot];
    for(j= inSTART; j<inEND-1; j++)
    {
        tExit = 0xFF;
        if(PrintData == 0xFF)
        {
            printf("\n ========================= \n");

            putchar(j + 0x30); putchar('\t');
            for(i=arrSTART; i<arrEND; i++)    
            {
                putchar(pBase[i] + 0x30); putchar(' '); 
            } 
            putchar('\t'); putchar(i_pivot + 0x30); putchar('\n');
        }

        for(i=inSTART; i<inEND; i++)
        {
            printf("\n \t CMP: %x <?> %x \n", pBase[i], pBase[i_pivot]);

            if(pBase[i] > pivotValue)
            {
                i_pivot--;
                if(i_pivot != i)   _SwapBytesInList(pBase, i_pivot, i_pivot+1); 
                _SwapBytesInList(pBase, i, i_pivot+1);
            
                tExit = 0x00;
                break;
            }
        }

        if(PrintData == 0xFF)
        {
            putchar(j + 0x30); putchar('\t');
            for(i=arrSTART; i<arrEND; i++)    
            {
                putchar(pBase[i] + 0x30); putchar(' '); 
            } 
            putchar('\t'); putchar(i_pivot + 0x30); putchar('\n');
        }

        if(tExit) break;
    }

        if(PrintData == 0xFF)
        {
            printf("\n ixd= %x pivot = %x \n", i_pivot, pBase[i_pivot]);
        }

    return i_pivot;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        SortQuickByte
 * @brief       Quick sort function
 * @param[in]   void 
 * @note        void 
 * @return      void 
*/
uint8_t SortQuickByte(uint8_t* pArray, uint8_t inSTART, uint8_t inEND, uint8_t inIDX_PIVOT)
{
    uint8_t i, j, tPivotValue;
    uint8_t exit;

    tPivotValue = pArray[inIDX_PIVOT];
    for(i= inSTART; i<inEND; i++)
    {// Outher loop for maximun posible     
        exit = 0xFF;
        for(j=inSTART; j<inEND; j++)
        {// Inner loop for compare pivot value 
            if(pArray[j] > tPivotValue)
            {
                inIDX_PIVOT--;
                if(inIDX_PIVOT != j)   _SwapBytesInList(pArray, inIDX_PIVOT, inIDX_PIVOT+1); 
                _SwapBytesInList(pArray, j, inIDX_PIVOT+1);
            
                exit = 0x00;
                break;  
            }
        }
        if(exit) break;
    }

    return inIDX_PIVOT;
}
//=====================================================================================================

void CallSortQuick1(void)
{
    //uint8_t pArrayOfByte[] = {5,3,4,8,1,2,4,9,6};
    uint8_t pArrayOfByte[] = {9,8,7,6,5,4,3,2,1};
    uint8_t pPivotIdx[8];
    uint8_t nmax = sizeof(pArrayOfByte);
    uint8_t i;
    // 1. Find pivot. It can be any element. 
    //      Any element at random
    //      The first or last element
    //      Middle element

    printf("\n List before: \n");
    for(i=0; i<nmax; i++)   {putchar(pArrayOfByte[i] + 0x30); putchar(' ');}

    pPivotIdx[0] = nmax - 1;// Last
    pPivotIdx[0] = _SplitListByPivot(pArrayOfByte, 0x00, nmax, pPivotIdx[0], 0, nmax, 0x00);

    printf("\n \n NEXT iteration ================= \n \n");
    
    //pPivotIdx[1] = nmax - 1;// Last
    //pPivotIdx[1] = _SplitListByPivot(pArrayOfByte, 0x01, nmax, pPivotIdx[1], 0, nmax);

    pPivotIdx[2] = nmax - 2;// Last
    pPivotIdx[2] = _SplitListByPivot(pArrayOfByte, 0x01, nmax-1, pPivotIdx[2], 0, nmax, 0xFF);

    pPivotIdx[3] = nmax - 3;// Last
    pPivotIdx[3] = _SplitListByPivot(pArrayOfByte, 0x02, nmax-2, pPivotIdx[3], 0, nmax, 0xFF);
}
void CallSortQuick2(void)
{
        //uint8_t pArrayOfByte[] = {5,3,4,8,1,2,4,9,6};
    uint8_t pArrayOfByte[] = {9,8,7,6,5,4,3,2,1};
    uint8_t pPivotIdx[8];
    uint8_t nmax = sizeof(pArrayOfByte);
    uint8_t i;
    // 1. Find pivot. It can be any element. 
    //      Any element at random
    //      The first or last element
    //      Middle element

    printf("\n List before: \n");
    for(i=0; i<nmax; i++)   {putchar(pArrayOfByte[i] + 0x30); putchar(' ');}

    i = SortQuickByte(pArrayOfByte, 0, nmax-1, nmax-1);

    printf("\n New pivot i= %x and lsit after: \n", i);
    for(i=0; i<nmax; i++)   {putchar(pArrayOfByte[i] + 0x30); putchar(' ');}

    i = SortQuickByte(pArrayOfByte, 1, nmax-2, nmax-2);

    printf("\n New pivot i= %x and lsit after: \n", i);
    for(i=0; i<nmax; i++)   {putchar(pArrayOfByte[i] + 0x30); putchar(' ');}

    i = SortQuickByte(pArrayOfByte, 2, nmax-3, nmax-3);

    printf("\n New pivot i= %x and lsit after: \n", i);
    for(i=0; i<nmax; i++)   {putchar(pArrayOfByte[i] + 0x30); putchar(' ');}

    i = SortQuickByte(pArrayOfByte, 3, nmax-4, nmax-4);

    printf("\n New pivot i= %x and lsit after: \n", i);
    for(i=0; i<nmax; i++)   {putchar(pArrayOfByte[i] + 0x30); putchar(' ');}
}
void CallSortQuick3(void)
{
    uint8_t pArrayOfByte[] = {9,8,7,6,5,4,3,2,1};
    uint8_t nmax = sizeof(pArrayOfByte);
    uint8_t i, j, k;  

    j = 0;
    for(k=0; k<3; k++)
    {

        j = SortQuickByte(pArrayOfByte, j, nmax-k, nmax-k);

        printf("\n New pivot i= %x and lsit after: \n", j);
        for(i=0; i<nmax; i++)   {putchar(pArrayOfByte[i] + 0x30); putchar(' ');}
    }
}