#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//====================================================================================================================================================
// Header for bubule sort
#define COMPARE_EQUAL   0x00
#define COMPARE_MORE    0x01
#define COMPARE_LESS    0xFF
uint8_t SortBubleBYTE(uint8_t* pArray, uint8_t inEleN, uint8_t inAscDsc);

typedef uint8_t (*pFunCompare_t)(uint8_t*, uint8_t*, uint8_t);
typedef void (*pFunMove_t)(uint8_t*, uint8_t*, uint8_t);
typedef struct 
{
    pFunCompare_t   pCompare;
    pFunMove_t      pMove;
    uint8_t         sortOrder;
    //uint8_t (*pCompare)(uint8_t*, uint8_t*, uint8_t);
    //void    (*pMove)(uint8_t*, uint8_t*, uint8_t);
}sortFunctionPointers_t;

uint8_t SortBubleForAllIntTypes(uint8_t* pBasePtr, uint8_t inNumOfEle, uint8_t inSizeOfEle, sortFunctionPointers_t* pFunStruct);
#define LIST_LENGHT 5
#define STRING_LEN 13
uint8_t SortBubleForStrArrTypes(char** ppArrStr, uint8_t inArrN, uint8_t inStrLen);

void CallSortBouble1(void);
void CallSortBouble2(void);
void CallSortBouble3(void);
void CallSortBouble4(void);
void CallSortBouble5(void);
//====================================================================================================================================================

//====================================================================================================================================================
// Header for quick sort
typedef struct 
{
    uint8_t maxlen;

}qSortHandler_t;

uint8_t SortQuickByte(uint8_t* pArray, uint8_t inSTART, uint8_t inEND, uint8_t inIDX_PIVOT); // Ret new position of index

inline void CallSortQuick1(void);
inline void CallSortQuick2(void);
//====================================================================================================================================================