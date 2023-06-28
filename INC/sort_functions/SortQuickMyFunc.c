#include "SortQuickMyFunc.h"

// Funkcja do wypisywania całej listy
/***********************************************************************************************
 * @name        PrintList
 * @brief       Funkcja do wypisywania całej listy
 * @param[in]   pNumbers    Wskaźnik do listy która wypisać.
 * @note        void
 * @return      void
 * @version     Version: 1,0
*/
void PrintListOfNumbers(uint8_t *pNumbers, uint8_t n)
{
    char ch;
    uint8_t i;
    printf("Lista: ");
    for(i=0; i<MAX_LIST_LEN; i++)
    {
        ch = pNumbers[i];
        if(ch == STR_END_MARK)
            break;

        printf("%d[%d] ", pNumbers[i],i);
    }
    printf("\n");
}

void SortBuble(uint8_t *pNumbers, uint8_t MAX)
{
    uint8_t i,n1,n2,tContinue,temp,n;
    uint8_t numList[8];

    printf("Before: :\n");
    for(i=0; i<MAX; i++){
        printf("%d ",*(pNumbers +i));
    }

    n=0;
    while(0xFF){
        tContinue = 0x00;
        n++;

        for(i=0; i<(MAX-1); i++){
            n1 = *(pNumbers + i);
            n2 = *(pNumbers + i + 1);
            if(n1 > n2){
                temp                = *(pNumbers + i);
                *(pNumbers + i)     = *(pNumbers + i + 1);
                *(pNumbers + i + 1) =  temp;
                tContinue = 0xFF;
            }
        }
        if(tContinue == 0x00){
            break;
        }
    }
    printf("\n\nAfter: :\n");
    for(i=0; i<MAX; i++){
        printf("%d ",*(pNumbers +i));
    }
    printf("\nNumbers of loops %d", n);
}

void SortQuick_v2(uint8_t *pNumbers, uint8_t MAX)
{
    uint8_t i,j, min, max, arrayLen;
    struct temp
    {
        uint32_t valMin;        uint32_t  valMax;
        uint8_t  indexMin;      uint8_t   indexMax;
        uint32_t buffor;
    }temp;
    
    PrintListOfNumbers(pNumbers, 0); //Dane przed sortowaniem

    if((MAX%2) == 0x00)
        arrayLen = MAX/2;

    if((MAX%2) == 0x01)
        arrayLen = (MAX - 0x01)/0x02;

    min = 0x00; 
    max = MAX - 0x01;
    
    for(j=0; j<arrayLen; j++)
    {
        temp.indexMin = min;        temp.indexMax = max;
        temp.valMin = pNumbers[j];  temp.valMax = pNumbers[j]; 
        //=======================================================================
        for(i=min; i<(MAX - min); i++)
        {
            #ifdef DEBUG
            printf("i=%d val=%d \n", i, pNumbers[i]);
            #endif
            if(temp.valMin > pNumbers[i]){
                temp.indexMin   = i; 
                temp.valMin     = pNumbers[i];}

            if(temp.valMax < pNumbers[i]){
                temp.indexMax   = i;
                temp.valMax     = pNumbers[i];}
        }
        #ifdef DEBUG 
        printf("min: %d; max: %d \n \n", temp.valMin, temp.valMax);
        #endif
        // Podmiania danych dla mimimalnego-------------------------------------
        temp.buffor     = pNumbers[min];
        pNumbers[min]   = temp.valMin;  
        pNumbers[temp.indexMin] = temp.buffor;
        //----------------------------------------------------------------------

        // Podmiana danych dla maksymalnego-------------------------------------
        if(temp.valMax == pNumbers[temp.indexMin])// Vale swap with max val
        {
            temp.buffor     = pNumbers[max];
            pNumbers[max]   = temp.valMax;
            pNumbers[temp.indexMin] = temp.buffor;
        }
        else
        {
            temp.buffor     = pNumbers[max];
            pNumbers[max]   = temp.valMax;
            pNumbers[temp.indexMax] = temp.buffor;
        }
        min++;  max--;
        //----------------------------------------------------------------------
    }
    PrintListOfNumbers(pNumbers, 0); //Dane posortowane
    printf("\n");
}