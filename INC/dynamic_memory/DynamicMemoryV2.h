#include <stdio.h>      /* printf, scanf, NULL */
#include <stdint.h>
#include <stdlib.h>     /* malloc, free, rand */

#define PRINT_TYPE_01   0x11
#define PRINT_TYPE_02   0x22
#define PRINT_TYPE_03   0x33
#define PRINT_TYPE_04   0x44

/*
#define DYNAMIC_ARRAY_DATA_OK       0x00U
#define DYNAMIC_ARRAY_NO_INIT       0x11U
#define DYNAMIC_ARRAY_NOELEMENT     0x22U
#define DYNAMIC_ARRAY_HEADPTR_NULL  0x33U
#define DYNAMIC_ARRAY_TAILPTR_NULL  0x44U
#define DYNAMIC_ARRAY_DATA_PRESENT  0x55U
#define DYNAMIC_ARRAY_REMOVE        0xFFU
*/
typedef enum 
{
    DYNAMIC_ARRAY_DATA_OK       = 0x00U,
    DYNAMIC_ARRAY_NO_INIT       = 0x11U,
    DYNAMIC_ARRAY_NOELEMENT     = 0x22U,
    DYNAMIC_ARRAY_HEADPTR_NULL  = 0x33U,
    DYNAMIC_ARRAY_TAILPTR_NULL  = 0x44U,
    DYNAMIC_ARRAY_DATA_PRESENT  = 0x55U,
    DYNAMIC_ARRAY_REMOVE        = 0xFFU
} DYNAMIC_ARRAY_StatusTypeDef;

#define DIRECTION_TAIL_TO_HEAD  0x01
#define DIRECTION_HEAD_TO_TAIL  0xFF

#define TRUE    0xFF
#define FALSE   0x00

#define DEBUG_ON    

#define DATA_LEN    12
typedef struct MemoryMember_t
{
    struct MemoryMember_t *pPrev;
    struct MemoryMember_t *pNext;
    uint8_t mydata[DATA_LEN];
}MemoryMember_t;

typedef void (*pFunPrint) (uint8_t*);

typedef struct
{
    struct MemoryMember_t *pTail;
    struct MemoryMember_t *pHead; 
    uint8_t n;
    uint8_t init;

    pFunPrint pFunSpecyfic;
}MallocControlData_t;


uint8_t AddFirstItem(MallocControlData_t* pControlData, uint8_t* pEle);

uint8_t AddHeadElement(MallocControlData_t* pControlData, uint8_t* pEle);
uint8_t AddTaillElement(MallocControlData_t* pControlData, uint8_t* pEle);

uint8_t RemoveHeadElement(MallocControlData_t* pControlData, uint8_t* pRet);
uint8_t RemoveTaillElement(MallocControlData_t* pControlData, uint8_t* pRet);

uint8_t GetHeadElement(MallocControlData_t* pControlData, uint8_t* pRet);
uint8_t GetTaillElement(MallocControlData_t* pControlData, uint8_t* pRet);
uint8_t GetRandomElement(MallocControlData_t* pControlData, uint8_t* pRet, uint8_t inIntex);

void PrintAllElements(MallocControlData_t* pControlData, uint8_t inDirection);

void RemoveAllElements(MallocControlData_t* pControlData);

DYNAMIC_ARRAY_StatusTypeDef CheckStackState(MallocControlData_t* pControlData);

void CallMyDynamicStackTest3(void);
void CallMyDynamicStackTest4(void);
