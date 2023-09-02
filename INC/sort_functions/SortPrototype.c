#include "SortPrototype.h"
#ifdef _SORT_PROTOTYPE_H

void PrintListOfNumbers_(uint8_t *pNumbers, uint8_t n)
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

/***********************************************************************************************
 * @name        SortQuick_v1
 * @brief       void
 * 
 * @param[in]   pNumbers    Wskaźnik do listy która wypisać.
 * @param[in]   MAX
 * 
 * @note        void
 * @return      void
 * @version     Version: 1,0
*/
void SortQuick_v1(uint8_t *pNumbers, uint8_t MAX)
{
    uint8_t i, min, max;
    struct temp{
        uint32_t valMin;
        uint32_t valMax;
        uint8_t indexMin;
        uint8_t indexMax;
        uint32_t buffor;
    }temp; 

    PrintListOfNumbers_(pNumbers, 0);
    // 1.
    i = 0;
    min=0;                      max=7;
    temp.indexMin = min;        temp.indexMax = max;  
    temp.valMin = pNumbers[i];  temp.valMax = pNumbers[i];
    for(i=0; i<(MAX - min); i++)
    {
        if(temp.valMin > pNumbers[i]){
            temp.indexMin = i; 
            temp.valMin = pNumbers[i]; 
        }
        if(temp.valMax < pNumbers[i]){
            temp.indexMax = i;
            temp.valMax = pNumbers[i];
        }
    }
    // Podmiania danych dla mimimalnego
    temp.buffor = pNumbers[min];
    pNumbers[min] = temp.valMin;
    i = temp.indexMin;  
    pNumbers[i] = temp.buffor; 
    // Podmiana danych dla maksymalnego
    temp.buffor = pNumbers[max];
    pNumbers[max] = temp.valMax;
    i = temp.indexMax;
    pNumbers[i] = temp.buffor;
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // 2.
    i = 1;
    min = 1;                    max = 6;
    temp.indexMin = min;        temp.indexMax = max; 
    temp.valMin = pNumbers[i];  temp.valMax = pNumbers[i];
    for(i=min; i<(MAX - min); i++)
    {
        if(temp.valMin > pNumbers[i]){
            temp.indexMin = i; 
            temp.valMin = pNumbers[i]; 
        }
        if(temp.valMax < pNumbers[i]){
            temp.indexMax = i;
            temp.valMax = pNumbers[i];
        }
    }
    // Podmiania danych dla mimimalnego
    temp.buffor = pNumbers[min];
    pNumbers[min] = temp.valMin;
    i = temp.indexMin;  
    pNumbers[i] = temp.buffor; 
    // Podmiana danych dla maksymalnego
    temp.buffor = pNumbers[max];
    pNumbers[max] = temp.valMax;
    i = temp.indexMax;
    pNumbers[i] = temp.buffor;
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // 3.
    i = 2;
    min = 2;                    max = 5;
    temp.indexMin = min;        temp.indexMax = max;
    temp.valMin = pNumbers[i];  temp.valMax = pNumbers[i];
    for(i=min; i<(MAX - min); i++)
    {
        if(temp.valMin > pNumbers[i]){
            temp.indexMin = i; 
            temp.valMin = pNumbers[i]; 
        }
        if(temp.valMax < pNumbers[i]){
            temp.indexMax = i;
            temp.valMax = pNumbers[i];
        }
    }
    // Podmiania danych dla mimimalnego
    temp.buffor = pNumbers[min];
    pNumbers[min] = temp.valMin;
    i = temp.indexMin;  
    pNumbers[i] = temp.buffor; 
    // Podmiana danych dla maksymalnego
    temp.buffor = pNumbers[max];
    pNumbers[max] = temp.valMax;
    i = temp.indexMax;
    pNumbers[i] = temp.buffor;
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // 4.
    min=3;                      max=4;
    temp.indexMin = min;        temp.indexMax = max;
    temp.valMin = pNumbers[i];  temp.valMax = pNumbers[i];
    for(i=3; i<(MAX-3); i++)
    {
        if(temp.valMin > pNumbers[i]){
            temp.indexMin = i; 
            temp.valMin = pNumbers[i]; 
        }
        if(temp.valMax < pNumbers[i]){
            temp.indexMax = i;
            temp.valMax = pNumbers[i];
        }
    }
    // Podmiania danych dla mimimalnego
    temp.buffor = pNumbers[min];
    pNumbers[min] = temp.valMin;
    i = temp.indexMin;  
    pNumbers[i] = temp.buffor; 
    // Podmiana danych dla maksymalnego
    temp.buffor = pNumbers[max];
    pNumbers[max] = temp.valMax;
    i = temp.indexMax;
    pNumbers[i] = temp.buffor;
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    PrintListOfNumbers_(pNumbers, 0);
    return;
}

#endif // _SORT_PROTOTYPE_H