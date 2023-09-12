#include "x00_generic_pointers.h"
#ifdef _X00_INCLUDE_GENERIC_POINTERS_H
/*****************************************************************************************
 * 
*/
void Call_DynamicMemoryAlocation_00(void)
{
    unsigned short int n = AMOUNT_OF_STRUCTURES;

    someStruct00_t* pFromMalloc = (someStruct00_t*)malloc(n * sizeof(someStruct00_t));
    someStruct00_t* pFromCalloc = (someStruct00_t*)calloc(n,  sizeof(someStruct00_t));

    printf("Call_DynamicMemoryAlocation_00() \n");

    printf("Data from malloc: %x \n", pFromMalloc->i);
    printf("Data from calloc: %x \n", pFromCalloc->i);

    printf("Call_DynamicMemoryAlocation_00() \n");

    free(pFromMalloc);
    free(pFromCalloc);
}

void Call_DynamicMemoryAlocation_01(void)
{
    char i;
    char* pChar;
    uint8_t len1, len2, lensep;

    len1 = strlen(STR1) + 1; // Plus null character on the end
    len2 = strlen(STR2) + 1; // Plus null character on the end
    lensep = strlen(CHAR_SEP) + 1;

    printf("strlen(STR1) = %d \n", len1);
    printf("strlen(STR2) = %d \n", len2);
    printf("strlen(CHAR_SEP) = %d \n");
    putchar('\n');

    pChar = (char*)malloc(len1);
    strncpy(pChar, STR1, len1);
    printf("ADDR: %x \n", pChar);
    printf("S1 = %s \n \n", pChar);

    pChar = (char*)realloc(pChar, len1 + len2 + 1);
    strncpy(pChar, STR1, len1);
    strcat(pChar,  " ");
    strcat(pChar,  STR2);
    printf("ADDR: %x \n", pChar);
    printf("S1 + S2 = %s \n", pChar);

    free(pChar);
}

void Call_DynamicMemoryAlocation_02(void)
{
    strAlocMem_t strAlocMem = {NULL, NULL, NULL, 0x00, 0x00, 0x00};

    strAlocMem.len1 = strlen(STR1) + 1;
    strAlocMem.len2 = strlen(STR2) + 1;

    strAlocMem.pStr1 = (char*)malloc(strAlocMem.len1);
    strAlocMem.pStr2 = (char*)malloc(strAlocMem.len2);

    printf("First part aloc memory and put data into: \n");
    strncpy(strAlocMem.pStr1, STR1, strAlocMem.len1);
    strncpy(strAlocMem.pStr2, STR2, strAlocMem.len2);
   
    printf("Str1: = %s \n", strAlocMem.pStr1);
    printf("Str2: = %s \n", strAlocMem.pStr2);
    putchar('\n');


    printf("Second part when move two str togather: \n");
    strAlocMem.pStr12 = (char*)realloc(strAlocMem.pStr1, strAlocMem.len1 + 1 + strAlocMem.len2);
    strcat(strAlocMem.pStr12, " ");
    strcat(strAlocMem.pStr12, strAlocMem.pStr2);
    printf("Full str1 and str2:= %s \n", strAlocMem.pStr12);
}
//========================================================================================

/*****************************************************************************************
 * Void pointer
*/
void Call_VoidTypePointer(void)
{
    char someArray[8];
    char i;

    void* pVoid = someArray;

    for(i=0; i<8; i++)
    {   someArray[i] = 0x11;}
    uint8_t* p1B = pVoid;
    *p1B = 0xFF;
    printf("- 0x%8x \n", *p1B);

    for(i=0; i<8; i++)
    {   someArray[i] = 0x22;}
    uint16_t* p2B = pVoid;
    *p2B = 0xFFFF;
    printf("- 0x%8x \n", *p2B);

    for(i=0; i<8; i++)
    {   someArray[i] = 0x33;}
    uint32_t* p4B = pVoid;
    *p4B = 0xFFFFFFFF;
    printf("- 0x%8x \n", *p4B);
}
//========================================================================================

//========================================================================================
#endif // _X00_INCLUDE_GENERIC_POINTERS_H