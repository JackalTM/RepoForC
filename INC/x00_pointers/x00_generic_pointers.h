#include "_x00_include.h"

#ifdef _X00_INCLUDE_GENERIC_POINTERS_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"

/*****************************************************************************************
 * Malloc and Calloc test with simple example
*/
#define AMOUNT_OF_STRUCTURES 0x01
typedef struct
{
    int i;
    int j;
    int k;
}someStruct00_t;

void Call_DynamicMemoryAlocation_00(void);

#define STR1 "STR1"
#define STR2 "STR2" 
#define CHAR_SEP (char)(' ')
typedef struct 
{
    char* pStr1;
    char* pStr2;
    char* pStr12;
    uint8_t len1;
    uint8_t len2;
    char separator;
}strAlocMem_t;


void Call_DynamicMemoryAlocation_01(void);
void Call_DynamicMemoryAlocation_02(void);
//========================================================================================

/*****************************************************************************************
 * Void pointer
*/

void Call_VoidTypePointer(void);
//========================================================================================

#endif // _X00_INCLUDE_GENERIC_POINTERS_H