#include "x00_generic_pointers.h"
#ifdef _X00_INCLUDE_GENERIC_POINTERS_H
/*****************************************************************************************
 * 
*/
void Call_GenericPointers_00(void)
{
    unsigned short int n = AMOUNT_OF_STRUCTURES;

    someStruct00_t* pFromMalloc = (someStruct00_t*)malloc(n * sizeof(someStruct00_t));
    someStruct00_t* pFromCalloc = (someStruct00_t*)calloc(n,  sizeof(someStruct00_t));

    printf("Call_GenericPointers_00() \n");

    printf("Data from malloc: %x \n", pFromMalloc->i);
    printf("Data from calloc: %x \n", pFromCalloc->i);

    printf("Call_GenericPointers_00() \n");

    free(pFromMalloc);
    free(pFromCalloc);
}
//========================================================================================
#endif // _X00_INCLUDE_GENERIC_POINTERS_H