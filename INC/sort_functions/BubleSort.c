#include "BubleSort.h"

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
void SortBubleINT(int* pArray, int inMAX, int* pSelfCall)
{
    int i,nmax, temp;
    uint8_t continueSort;
    nmax = 0x00;
    do
    {   continueSort = 0x00; nmax++;
        for(i=1; i<inMAX; i++)
        {
            if(pArray[i-1] > pArray[i])
            {   continueSort = 0xFF;
                //putchar(pArray[i-1] + 0x30); putchar(' '); putchar(pArray[i] + 0x30); putchar(' '); putchar(i + 0x30); putchar('\n');
                temp = pArray[i-1];
                pArray[i-1] = pArray[i];
                pArray[i] = temp;
                *pSelfCall = *pSelfCall + 0x01;
            }
        }
    } 
    while((continueSort == 0xFF) && (1));
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
    //SortBubleINT(byteArray, sizeof(byteArray), 0xFF);
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
    tFunStruct.pCompare    = (pFunCompare_t)&_CompareElementStr;
    tFunStruct.pMove       = (pFunMove_t)&_MoveElementANY;
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






