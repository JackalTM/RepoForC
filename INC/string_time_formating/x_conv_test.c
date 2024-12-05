#include "x_conv_test.h"

void CALL_converstion_test(void)
{
    char pBuffer[] = {"000000000000000"};
    char tchar;

    unsigned int i, j;
    for(i=0; i<16; i++)
    {
        j = i + 5;
        CUST_CONV_TimeToStr_hh_mm_ss_args(j+1, j+2, j+3, pBuffer);    
        printf("-- i= %d | time= %s \n", j, pBuffer);
    }

}