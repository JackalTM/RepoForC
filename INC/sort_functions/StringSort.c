#include "StringSort.h"
#ifdef _STRING_SORT_H

//#define DEBUG1

// Funkcja do wypisywania całej listy
/***********************************************************************************************
 * @name        PrintList
 * @brief       Funkcja do wypisywania całej listy
 * @param[in]   pNumbers    Wskaźnik do listy która wypisać.
 * @note        void
 * @return      void
 * @version     Version: 1,0
*/
void PrintList(uint8_t *pNumbers)
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
//==============================================================================================

/***********************************************************************************************
 * @name        MoveStr_Dest_Source(char *pStrDest, char *pStrSource)
 * @brief       Przenoszenie całego łańcucha znakowego w inne miejsce
 * 
 * @param[in]   pStrDest    Wskaźnik docelowego łańcucha
 * @param[in]   pStrSource  Wskaźnik źrudłowego łańcucha
 * 
 * @note        
 * @return      void
 * @version     Version: 1,1
*/
void MoveStr_Dest_Source(char *pStrDest, char *pStrSource)
{
    // Made by Nihilanth
    // Version: 1,1
    char ch;
    uint8_t i;
    for(i=0; i<MAX_STRING_LEN; i++)
    {
        ch = pStrSource[i];
        if(ch == STR_END_MARK) // Znak 0x00 to koniec stringa
        {
            pStrDest[i] = 0x00;
            return;
        }
        pStrDest[i] = ch;
    }
    i = MAX_STRING_LEN - 1;
    pStrDest[i] = 0x00;
    return;
}
//==============================================================================================

/***********************************************************************************************
 * @name        uint8_t CompareString(char *str11, char *str22)     
 * @brief       Porównywanie dwóch łancuchów znakowych. 
 * 
 * @param[in]   str11   Wskaźnik do pierwszego łańcucha
 * @param[in]   str22   Wskaźnik do drugiego łańcucha
 * 
 * @note        Legend:    
 * @note        0x00 - strings are equal
 * @note        0x11 - First string highter value
 * @note        0x22 - Second string highter calue
 * @note        0xFF - String compare error
 * 
 * @return      state of compared strings
 * @version     Version: 1,0
*/
uint8_t CompareString(char *str11, char *str22)
{
    char ch1, ch2;  
    uint8_t i;
    for(i=0; i<MAX_STRING_LEN; i++)
    {   
        ch1 = str11[i]; 
        ch2 = str22[i];
        // Sprawdzanie czy ostatni znak to zdefiniowany---------------------------------------
        if((ch1 == STR_END_MARK) && (ch2 == STR_END_MARK)) // String end in the same lenght 
            return 0x00;
        //------------------------------------------------------------------------------------
        if((ch1 != STR_END_MARK) && (ch2 == STR_END_MARK)) // Str11 longer than Str22
            return 0x11;
        //------------------------------------------------------------------------------------
        if((ch1 == STR_END_MARK) && (ch2 != STR_END_MARK)) // Str22 longer than Str11
            return 0x22;
        //------------------------------------------------------------------------------------       

        // str11 value is greater than str22------------------
        if(ch1 > ch2) 
            return 0x11;
        //----------------------------------------------------

        // str22 value is greater than str11------------------
        if(ch1 < ch2)
            return 0x22;
        //----------------------------------------------------
    }
    return 0xFF;// Error value
}
//==============================================================================================

/***********************************************************************************************
 * @name            SortQuickString(char **ppStrings, uint8_t iListMaxLen)
 * @brief           Sortowanie łańcuchów znakowych
 * 
 * @param[in]       ppStrings   Podwójny wskanźnik do operacji na łancuchu znakowym
 * @param[in]       iListMaxLen Maksymalna długośc łanucha znakowego
 * 
 * @note        
 * @return      
*/
void SortQuickString(char **ppStrings, uint8_t iListMaxLen)
{
    // Made by Nihilanth
    // Version: 1,0 Problem 
    // Version: 1,1 Fixed working
    uint8_t i, j;
    struct  
    {
        uint8_t     indexMinValue;      // Index where value is minimum
        uint8_t     minBound;           // Loop bound from bottom
        uint8_t     indexMaxValue;      // Index where value is maximum
        uint8_t     maxBound;           // Loop bound from upper
        uint8_t     arrayHalfLenLoop;   // Half lenght of loop lenght
        uint8_t     compareResoult;     // Resoult of compare string 
        char        strMin[MAX_STRING_LEN];     // Minimal value string
        char        strMax[MAX_STRING_LEN];     // Maximum value string
        char        strBuffor[MAX_STRING_LEN];  // Temp buffor
    }temp;

    #pragma region // Iniciowanie wartości początkowych. 
    // Zainiciowanie wartości początkowych sortowania. Sledzenie zwęrzania sie pętli
    temp.minBound = 0x00;                   // Minimalna zaczyna sie od zera
    temp.maxBound = (iListMaxLen - 0x01);   // Maksymalna zaczyna sie od (max - 1)

    // Przypadki gdy lista string jest parzysta lub nieparzysta
    temp.compareResoult = (iListMaxLen % 2);
    switch (temp.compareResoult)
    {
        case 0x0:
            temp.arrayHalfLenLoop = (iListMaxLen / 2);
            break;

        case 0x1:
            temp.arrayHalfLenLoop = ((iListMaxLen - 0x01) / 0x02);
            break;
        
        default:
            break;
    }
    #pragma endregion
 
    for(j=0; j<temp.arrayHalfLenLoop; j++)
    {// Pierwsza zewnętrzna pętla dla długości prez dwa
        temp.indexMinValue = temp.minBound;        
        temp.indexMaxValue = temp.maxBound;
        MoveStr_Dest_Source(temp.strMin, ppStrings[j]); 
        MoveStr_Dest_Source(temp.strMax, ppStrings[j]); 

        for(i=temp.minBound; i<(iListMaxLen - temp.minBound); i++)
        {// Pęta zwęrza sie ko środkowi
            temp.compareResoult = CompareString(temp.strMin, ppStrings[i]);
            if(temp.compareResoult == 0x11)
            {
                temp.indexMinValue   = i; 
                MoveStr_Dest_Source(temp.strMin, ppStrings[i]);
            }

            temp.compareResoult = CompareString(temp.strMax, ppStrings[i]);
            if(temp.compareResoult == 0x22)
            {
                temp.indexMaxValue   = i;
                MoveStr_Dest_Source(temp.strMax, ppStrings[i]);
            }
        }
        
        #pragma region // Podmiania danych dla mimimalnego
        MoveStr_Dest_Source(temp.strBuffor, ppStrings[temp.minBound]);
        MoveStr_Dest_Source(ppStrings[temp.minBound], temp.strMin);
        MoveStr_Dest_Source(ppStrings[temp.indexMinValue], temp.strBuffor);
        #pragma endregion

        #pragma region // Podmiania danych dla maksymalnego
        MoveStr_Dest_Source(temp.strBuffor, ppStrings[temp.maxBound]);
        MoveStr_Dest_Source(ppStrings[temp.maxBound], temp.strMax);;
        temp.compareResoult = CompareString(temp.strMax, ppStrings[temp.indexMinValue]);
        if(temp.compareResoult == 0x00)
        {   
            MoveStr_Dest_Source(ppStrings[temp.indexMinValue], temp.strBuffor);   
        }
        else
        {
            MoveStr_Dest_Source(ppStrings[temp.indexMaxValue], temp.strBuffor);
        }
        #pragma endregion

        temp.minBound++;  
        temp.maxBound--;
    }
    return;
}
//==============================================================================================

/***********************************************************************************************
 * @name        
 * @brief       
 * @param[in]   
 * @note        
 * @return      
*/
void SortQuickInt(uint8_t *pNumbers, uint8_t maxLen)
{
    uint8_t i,j, min, max, arrayLen;
    struct temp
    {
        uint32_t valMin;        uint32_t  valMax;
        uint8_t  indexMin;      uint8_t   indexMax;
        uint32_t buffor;
    }temp;

    if((maxLen % 2) == 0x00)
        arrayLen = maxLen / 2;

    if((maxLen % 2) == 0x01)
        arrayLen = (maxLen - 0x01) / 0x02;

    min = 0x00; 
    max = maxLen - 0x01;
    
    for(j=0; j<arrayLen; j++)
    {
        temp.indexMin = min;        temp.indexMax = max;
        temp.valMin = pNumbers[j];  temp.valMax = pNumbers[j]; 
        //====================================================
        for(i=min; i<(maxLen - min); i++)
        {
            if(temp.valMin > pNumbers[i]){
                temp.indexMin   = i; 
                temp.valMin     = pNumbers[i];}

            if(temp.valMax < pNumbers[i]){
                temp.indexMax   = i;
                temp.valMax     = pNumbers[i];}
        }
        
        #pragma region // Podmiania danych dla mimimalnego
        temp.buffor     = pNumbers[min];
        pNumbers[min]   = temp.valMin;  
        pNumbers[temp.indexMin] = temp.buffor;
        #pragma endregion

        
        #pragma region // Podmiana danych dla maksymalnego
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
        #pragma endregion
        min++;  max--;
    }
    return;
}

void CallTestSort(void)
{
    ;
}

#endif // _STRING_SORT_H