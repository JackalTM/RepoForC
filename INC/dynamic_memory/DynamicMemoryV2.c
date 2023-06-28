#include "DynamicMemoryV2.h"

/*******************************************************************************************************************
 * @name    CheckForErros
 * @brief   Check data in terms of worng content
 * @param[in] pContrldata Pointer to control stucture
 * @return State of error if present
 * @note This is static private function
*/
DYNAMIC_ARRAY_StatusTypeDef CheckStackState(MallocControlData_t* pControlData)
{
    DYNAMIC_ARRAY_StatusTypeDef tStatus;

    if(pControlData->init != TRUE)          
        tStatus = DYNAMIC_ARRAY_NO_INIT;
    else if(pControlData->n == 0x00)        
        tStatus = DYNAMIC_ARRAY_NOELEMENT;
    else if(pControlData->pHead == NULL) 
        tStatus = DYNAMIC_ARRAY_HEADPTR_NULL;
    else if(pControlData->pTail == NULL)   
        tStatus = DYNAMIC_ARRAY_TAILPTR_NULL; 
    else       
        tStatus = DYNAMIC_ARRAY_DATA_OK;                             

    return tStatus;
}
//==================================================================================================================

/*******************************************************************************************************************
 *@name     AddFirstItem
 *@brief    Return last element from dynamic array to given pointer
 *@param    pContrldata     Pointer to control data
 *@param    pEle            Start addr for data to put inside
 *@return   Status of the operation
*/
uint8_t AddFirstItem(MallocControlData_t* pControlData, uint8_t* pEle)
{
    MemoryMember_t* pFirstElement;
    pFirstElement = ((MemoryMember_t*)malloc(sizeof(MemoryMember_t)));

    #ifdef DEBUG_ON
        printf("Aloc ADDR:= 0x%08x \n", pFirstElement);
    #endif

    pFirstElement->pPrev = NULL;
    pFirstElement->pNext = NULL;

    pControlData->pTail = pFirstElement;
    pControlData->pHead = pFirstElement;
    pControlData->n     = 0x01;
    pControlData->init  = TRUE;

    uint8_t i;
    for(i=0; i<DATA_LEN; i++)
    {
        pFirstElement->mydata[i] = pEle[i];
    }
    return 0x00;
}
//================================================================================================================

/*****************************************************************************************************************
 *@name     AddHeadElement
 *@brief    Add element on the HEAD of array

 *@param    pContrldata     Pointer to control data
 *@param    pEle            Start addr for data to put inside

 *@return   Status of the operation
*/
uint8_t AddHeadElement(MallocControlData_t* pControlData, uint8_t* pEle)
{
    uint8_t temp;
    temp = CheckStackState(pControlData);
    if(temp) return temp;

    MemoryMember_t* pNewHead; 
    MemoryMember_t* pOldHead;
    
    //1. New alocated memory.
    pNewHead = ((MemoryMember_t*)malloc(sizeof(MemoryMember_t)));
    pOldHead = pControlData->pHead;

    #ifdef DEBUG_ON
        printf("Aloc ADDR:= 0x%08x \n", pNewHead);
    #endif
    
    pOldHead->pNext = pNewHead;
    pNewHead->pPrev = pOldHead;
    pNewHead->pNext = NULL;

    pControlData->pHead = pNewHead;
    pControlData->n++;

    // 
    uint8_t i, j;
    for (i=0; i<DATA_LEN; i++)
    {
        pNewHead->mydata[i] = pEle[i];
    }
    return 0x00;
}
//================================================================================================================

/*****************************************************************************************************************
 *@name     AddTaillElement
 *@brief    Add element on the TAILL of array

 *@param    pContrldata     Pointer to control data
 *@param    pEle            Start addr for data to put inside

 *@return   Status of the operation
*/
uint8_t AddTaillElement(MallocControlData_t* pControlData, uint8_t* pEle)
{
    uint8_t temp;
    temp = CheckStackState(pControlData);
    if(temp) return temp;

    MemoryMember_t* pNewTail;
    MemoryMember_t* pOldTail;

    pNewTail = ((MemoryMember_t*)malloc(sizeof(MemoryMember_t)));
    pOldTail = pControlData->pTail; 

    #ifdef DEBUG_ON
        printf("Aloc ADDR:= 0x%08x \n", pNewTail);
    #endif

    pOldTail->pPrev = pNewTail;
    pNewTail->pNext = pOldTail;
    pNewTail->pPrev = NULL;

    pControlData->pTail = pNewTail;
    pControlData->n++;

    uint8_t i,j;
    for(i=0; i<DATA_LEN; i++)
    {
        pNewTail->mydata[i] = *(pEle + i);
    }
    return 0x00;
}
//================================================================================================================

/*****************************************************************************************************************
 *@name     RemoveHeadElement
 *@brief    Return last element from dynamic array to given pointer
 *@param    pContrldata to control data
 *@param    pRet start addr to place data
 *@param    inRemove remove or not last element
 *@return   Status of the operation
*/
uint8_t RemoveHeadElement(MallocControlData_t* pControlData, uint8_t* pRet)
{
    uint8_t temp;
    temp = CheckStackState(pControlData);
    if(temp) return temp;

    MemoryMember_t* pOldHead;
    MemoryMember_t* pNewHead;
    uint8_t i;

    // 1. Return head element
    pOldHead = pControlData->pHead;
    pNewHead = pOldHead->pPrev;
    for (i=0; i<DATA_LEN; i++)
    {
        *(pRet + i) = pOldHead->mydata[i];
    }

    // 3. Removing element from memory
    if((pControlData->pTail == pControlData->pHead) || (pControlData->n == 0x1))
    {// Last element is present
        pControlData->pTail = NULL;
        pControlData->pHead = NULL;
        pControlData->n     = 0x00;
        pControlData->init  = 0x00;
    }
    else if(pControlData->n > 0x1)
    {// More than 1 element is present
        pNewHead->pNext = NULL;
        pControlData->pHead = pNewHead;
        if(pControlData->n > 0x00)
            pControlData->n--;
    }
    else // Other cases
    {   return FALSE;}

    #ifdef DEBUG_ON
        printf("free ADDR:= 0x%08x \n", pOldHead);
    #endif

    // 4. Return ocupieted memory
    free((MemoryMember_t*)pOldHead);
    return TRUE;
}
//================================================================================================================

/*****************************************************************************************************************
 *@name     RemoveTaillElement
 *@brief    Return last element from dynamic array to given pointer
 *@param    pContrldata to control data
 *@param    pRet start addr to place data
 *@param    inRemove remove or not last element
 *@return   Status of the operation
*/
uint8_t RemoveTaillElement(MallocControlData_t* pControlData, uint8_t* pRet)
{
    uint8_t temp = CheckStackState(pControlData);
    if(temp) return temp;

    MemoryMember_t* pNewTail;
    MemoryMember_t* pOldTail;

    pOldTail = pControlData->pTail;
    pNewTail = pOldTail->pNext;
    uint8_t i;
    for(i=0; i<DATA_LEN; i++)
    {
        *(pRet + i) = pOldTail->mydata[i];
    }

    if((pControlData->pTail == pControlData->pHead) || (pControlData->n == 0x1))
    {
        pControlData->pTail = NULL;
        pControlData->pHead = NULL;
        pControlData->n     = 0x00;
        pControlData->init  = 0x00;
    }
    else if(pControlData->n > 0x1)
    {
        pNewTail->pPrev = NULL;
        pControlData->pTail = pNewTail;
        if(pControlData->n > 0x00)
            pControlData->n--;
    }
    else
    {   return FALSE;}

    #ifdef DEBUG_ON
        printf("free ADDR:= 0x%08x \n", pOldTail);
    #endif

    free((MemoryMember_t*)pOldTail);
    return TRUE;
}
//================================================================================================================

/*****************************************************************************************************************
 *@name     GetHeadElement
 *@brief    Return last element from dynamic array to given pointer
 *@param    pContrldata to control data
 *@param    pRet start addr to place data
 *@return   Status of the operation
*/
uint8_t GetHeadElement(MallocControlData_t* pControlData, uint8_t* pRet)
{
    uint8_t i;
    uint8_t temp = CheckStackState(pControlData);
    if(temp) return temp;

    MemoryMember_t* pHead = pControlData->pHead;
    for(i=0; i<DATA_LEN; i++)
    {
        pRet[i] = pHead->mydata[i];
    }
}
//================================================================================================================

/*****************************************************************************************************************
 *@name     GetTaillElement
 *@brief    Return last element from dynamic array to given pointer
 *@param    pContrldata to control data
 *@param    pRet start addr to place data
 *@return   Status of the operation
*/
uint8_t GetTaillElement(MallocControlData_t* pControlData, uint8_t* pRet)
{
    uint8_t i;
    uint8_t temp = CheckStackState(pControlData);
    if(temp) return temp;

    MemoryMember_t* pTail = pControlData->pTail;
    for(i=0; i<DATA_LEN; i++)
    {
        pRet[i] = pTail->mydata[i];
    }
}
//================================================================================================================

/*****************************************************************************************************************
 *@name     GetRandomElement
 *@brief    Return specyfis element from list
 *@param    pContrldata to control data
 *@param    pEle start addr to place data
 *@param    inIntex Index of emement to return
 *@return   Status of the operation
*/
uint8_t GetRandomElement(MallocControlData_t* pControlData, uint8_t* pRet, uint8_t inIntex)
{
    if(inIntex >= pControlData->n) return 0xFF;

    uint8_t tDirection,i;
    MemoryMember_t* pTemp;

    tDirection = inIntex / pControlData->n;
    if(tDirection > (pControlData->n / 2))
    {   pTemp = pControlData->pHead;
        inIntex = inIntex - pControlData->n;
        for (i=0; i < inIntex; i++)
        {
            pTemp = pTemp->pPrev;
        }
    }
    else
    {   pTemp = pControlData->pTail;
        for (i=0; i < inIntex; i++)
        {
            pTemp = pTemp->pNext;
        }
    }    
    
    for(i=0; i<DATA_LEN; i++)
    {
        pRet[i] = pTemp->mydata[i];
    }

    return 0x00;
}
//================================================================================================================

/*****************************************************************************************************************
 *@name     RemoveAllElements
 *@brief    Remove all elements from list
 *@param    pContrldata to control data
 *@return   void
*/
void RemoveAllElements(MallocControlData_t* pControlData)
{
    MemoryMember_t* pTemp = pControlData->pTail;
    uint8_t i, n;

    if(! pControlData->init) return;
    n = pControlData->n;
    for (i = 0; i < pControlData->n; i++)
    {
        if(n >= 0x02)
        {   pTemp = pTemp->pNext;
            free(pTemp->pPrev);
#ifdef DEBUG_ON
            printf("free ADDR:= 0x%08x \n", pTemp->pPrev);
#endif
        }
        else
        {   free(pTemp);
#ifdef DEBUG_ON
            printf("free ADDR:= 0x%08x \n", pTemp);
#endif
        }
        n--;
    }
}
//================================================================================================================

/*****************************************************************************************************************
 *@name     PrintAllElements
 *@brief    Print on screen all elements in pointer stack.

 *@param[in]    pContrldata Pointer to structure with control data
 *@param[in]    inDirection Print from head to tail or form tail to head

 *@return   Void
*/
void PrintAllElements(MallocControlData_t* pControlData, uint8_t inDirection)
{
    uint8_t stackstate = CheckStackState(pControlData);
    if(stackstate)
    {
        printf("EMPTY \n");
        return;
    }

    MemoryMember_t* pTemp;
    uint8_t i;

    if(inDirection == DIRECTION_TAIL_TO_HEAD)
        pTemp = pControlData->pTail;
    else if(inDirection == DIRECTION_HEAD_TO_TAIL)
        pTemp = pControlData->pHead;
    else
        return;

    printf("\n --- \n");
    for (i=0; i < pControlData->n; i++)
    {
        (*pControlData->pFunSpecyfic)(pTemp->mydata);

        if(inDirection == DIRECTION_TAIL_TO_HEAD)       
            pTemp = pTemp->pNext;
        else if(inDirection == DIRECTION_HEAD_TO_TAIL)
            pTemp = pTemp->pPrev;
        else
            return;
    }
    printf("\n --- \n");
}
//================================================================================================================

typedef struct 
{
    uint8_t index;
    uint32_t num1;
    uint32_t num2;
}oneRow_t;
static void _PrintSpecStruct(uint8_t* pBase)
{
    oneRow_t* ptemp = (oneRow_t*)pBase;

    putchar('\n');
    printf("[%x] | ", ptemp->index);
    printf("ADDR:= 0x%08x | ", ptemp);
    printf("DATA1:= 0x%x |", ptemp->num1);
    printf("DATA2:= 0x%x \n", ptemp->num2);
    putchar('\n');
}

//================================================================================================================
void CallMyDynamicStackTest3(void)
{
    MallocControlData_t mallControl;
    mallControl.pFunSpecyfic = &_PrintSpecStruct;
    uint64_t tdata;
    uint8_t retval;

    printf("Alocating memory \n");

    tdata = 0x11;
    retval = AddFirstItem(&mallControl, (uint8_t*)&tdata);
    PrintAllElements(&mallControl, DIRECTION_HEAD_TO_TAIL);
    
    tdata = 0x22;
    //retval= AddTaillElement(&mallControl, (uint8_t*)&tdata);
    retval= AddHeadElement(&mallControl, (uint8_t*)&tdata);
    PrintAllElements(&mallControl, DIRECTION_HEAD_TO_TAIL);

    tdata = 0x33;
    retval= AddHeadElement(&mallControl, (uint8_t*)&tdata);
    PrintAllElements(&mallControl, DIRECTION_HEAD_TO_TAIL);

    printf("Releasing memory \n \n");

    do
    {
        PrintAllElements(&mallControl, DIRECTION_HEAD_TO_TAIL);
        printf("Next call \n");
        retval = RemoveHeadElement(&mallControl, (uint8_t*)&tdata);
        //retval = RemoveTaillElement(&mallControl, (uint8_t*)&tdata, TRUE);
    } 
    while (retval == TRUE);
}
//================================================================================================================

//================================================================================================================
void CallMyDynamicStackTest4(void)
{
    MallocControlData_t mallControl;
    oneRow_t row1, row2, row3,temp;
    mallControl.pFunSpecyfic = &_PrintSpecStruct;
    
    row1.index = 1;
    row1.num1 = 0xAAAA;
    row1.num2 = 0xBBBB;

    row2.index = 2;
    row2.num1 = 0xCCCC;
    row2.num2 = 0xDDDD;

    row3.index = 3;
    row3.num1 = 0xEEEE;
    row3.num2 = 0xFFFF;

    AddFirstItem(&mallControl, (uint8_t*)&row1);
    AddHeadElement(&mallControl, (uint8_t*)&row2);
    AddHeadElement(&mallControl, (uint8_t*)&row3);

    PrintAllElements(&mallControl, DIRECTION_TAIL_TO_HEAD);

    GetRandomElement(&mallControl, (uint8_t*)&temp, 0);
    printf("Data: %x | %x | %x \n", temp.index, temp.num1, temp.num2);

    GetRandomElement(&mallControl, (uint8_t*)&temp, 1);
    printf("Data: %x | %x | %x \n", temp.index, temp.num1, temp.num2);

    GetRandomElement(&mallControl, (uint8_t*)&temp, 2);
    printf("Data: %x | %x | %x \n", temp.index, temp.num1, temp.num2);

    RemoveAllElements(&mallControl);
}