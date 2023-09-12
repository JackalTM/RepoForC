#include "_x00_include.h"
#ifdef _X01_INCLUDE_LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_AMOUNT 4
#define OPERATION_FAULT 0xFF
#define OPERATION_SUCESS 0x00
#define FIRST_ELEMENT 0
#define LAST_ELEMENT -1

typedef struct listItem
{
    struct listItem* pNEXT;
    struct listItem* pPREV;
    int iData;
}listItem_t;

typedef struct 
{
    listItem_t* pHead;
    listItem_t* pTail;

    int iAmount;
}listInfo_t;


char ListInit(listInfo_t* plistInfo, int* piElement);

char ListPutHead(listInfo_t* plistInfo, int* piElement);
char ListPutTail(listInfo_t* plistInfo, int* piElement);

char ListGetHead(listInfo_t* plistInfo, int* piElement);
char ListGetTail(listInfo_t* plistInfo, int* piElement);
char ListGetElement(listInfo_t* plistInfo, int* piElement, int n);

char ListRemoveHead(listInfo_t* plistInfo, int* piElement);
char ListRemoveTail(listInfo_t* plistInfo, int* piElement);

#endif // _X01_INCLUDE_LINKED_LIST_H