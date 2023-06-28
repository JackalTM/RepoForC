#include <stdio.h>      /* printf, scanf, NULL */
#include <stdint.h>
#include <stdlib.h>     /* malloc, free, rand */

#define PRINT_TYPE_01   0x11
#define PRINT_TYPE_02   0x22
#define PRINT_TYPE_03   0x33
#define PRINT_TYPE_04   0x44

#define DYNAMIC_ARRAY_REMOVE        0xFF
#define DYNAMIC_ARRAY_NO_ELEMENT    0x11
#define DYNAMIC_ARRAY_PTR_NULL      0x22
#define DYNAMIC_ARRAY_DATA_VALID    0x33
#define DYNAMIC_ARRAY_DATA_PRESENT  0x44

#define DATA_LEN    8
typedef struct MemoryMember_t
{
    struct MemoryMember_t *pPrev;
    struct MemoryMember_t *pNext;
    uint8_t mydata[DATA_LEN];
}MemoryMember_t;

typedef struct
{
    struct MemoryMember_t *pStartPtr;
    struct MemoryMember_t *pEndPtr; 
    uint8_t n;
    uint8_t contentSize;
}MallocControlData_t;

void Copydata(uint8_t* inData, uint8_t* outData, uint8_t byteLen);
void _AddFirstItem(MallocControlData_t* pContrldata,char inData[]);
void AddItemToEnd(MallocControlData_t* pContrldata,char inData[]);
void AddItemOnFront(MallocControlData_t* pContrldata,char inData[]);

uint8_t GetElement(MallocControlData_t* pContrldata, uint8_t elNum, uint8_t *parray[]);

uint64_t RemoveAndGetFirst(MallocControlData_t* pContrldata);
uint64_t RemoveAndGetLast(MallocControlData_t* pContrldata);
uint8_t RemoveAllObj(MallocControlData_t* pContrldata, uint8_t objsize);

void PrintFromDynamicArray(MallocControlData_t* pContrldata,uint8_t printType);

uint8_t DynamicStackTest1(uint8_t exit);
uint8_t DynamicStackTest2(uint8_t exit);