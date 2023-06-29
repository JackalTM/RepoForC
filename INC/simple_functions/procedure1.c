#include "procedure1.h"

void GetBitWiseOperation(uint8_t n)
{
    uint32_t retVal[32];
    uint8_t i, j;

    for(i=0; i<n; i++)
    {
        retVal[i] = ~(1 << i);
    }

    printf("Evey MASK for \n", 0);
    for(i=0; i<n; i++)
    {
        printf("#define MASK_TRUE_BIT_%0.2i 0x%0.8xU \n",i , retVal[i]);
    }
}