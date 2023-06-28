#include "dynamicmemory.h"

/*****************************************************************************
* name  - Copydata
* breaf - This function copy data from source to destiny. Data format is not valid.
* in    - Pointer to source data
* in    - Pointer to destiny data
* in    - Data size in bytes
* ret   - void
******************************************************************************/
void Copydata(uint8_t* inData, uint8_t* outData, uint8_t byteLen)
{
    uint8_t i;
    for(i=0; i<byteLen; i++)
    {
        *(outData + i) = *(inData + i);
    }
}
//============================================================================

/*****************************************************************************
* name  - AddFirstItem
* breaf - This function add first item to dynamic memory member
* in    - Pointer to global data wchitch contains taill and head of pointers
* in    - Data to put inside memory member
* ret   - void
******************************************************************************/
void _AddFirstItem(MallocControlData_t* pContrldata, char* inData)
{
    if(pContrldata->n != 0x00)
        return;

    MemoryMember_t* pTemp;
    uint8_t dataLenght;

    pTemp = ((MemoryMember_t*)malloc(sizeof(MemoryMember_t))); 
    pContrldata->pStartPtr  = pTemp;
    pContrldata->pEndPtr    = pTemp;
    pContrldata->n          = 0x01;
    pTemp->pPrev            = NULL;
    pTemp->pNext            = NULL;

    dataLenght = DATA_LEN * (sizeof(char));
    Copydata(inData, pTemp->mydata, dataLenght);
}
//============================================================================

/*****************************************************************************
* name  - AddItemOnFront
* breaf - This function add item to dynamic memory member on head
* in    - Pointer to global data wchitch contains taill and head of pointers
* in    - Data to put inside memory member
* ret   - void
******************************************************************************/
void AddItemOnFront(MallocControlData_t* pContrldata, char* inData)
{
    if(pContrldata->n == 0x00)
        return;

    MemoryMember_t *pNew, *pOld;
    uint8_t dataLenght;
    
    pOld = pContrldata->pStartPtr;
    pContrldata->pStartPtr = ((MemoryMember_t*)malloc(sizeof(MemoryMember_t)));
    pOld->pPrev = pContrldata->pStartPtr;

    pNew = pContrldata->pStartPtr;
    pNew->pPrev = NULL;
    pNew->pNext = pOld;

    pContrldata->n = pContrldata->n + 0x01;

    dataLenght = DATA_LEN * (sizeof(char));
    Copydata(inData, pNew->mydata, dataLenght);
}
//============================================================================

/*****************************************************************************
* name  - AddItemToEnd
* breaf - This function add item to dynamic memory member on taill
* in    - Pointer to global data wchitch contains taill and head of pointers
* in    - Data to put inside memory member
* ret   - void
******************************************************************************/
void AddItemToEnd(MallocControlData_t* pContrldata, char* inData)
{
    if(pContrldata->n == 0x00)
        return;

    MemoryMember_t *pNew, *pOld;
    uint8_t dataLenght;

    pOld = pContrldata->pEndPtr;
    pContrldata->pEndPtr = ((MemoryMember_t*)malloc(sizeof(MemoryMember_t)));
    pOld->pNext = pContrldata->pEndPtr;

    pNew = pContrldata->pEndPtr;
    pNew->pNext = NULL;
    pNew->pPrev = pOld;

    pContrldata->n = pContrldata->n + 0x01;

    dataLenght = DATA_LEN * (sizeof(char));
    Copydata(inData, pNew->mydata, dataLenght);
}
//============================================================================

/*****************************************************************************
* name  - GetElement
* breaf - Return content of demand object
* in    - Pointer to global data wchitch contains taill and head of pointers
* in    - Data to put inside memory member
* ret   - void
******************************************************************************/
uint8_t GetElement(MallocControlData_t* pContrldata, uint8_t elNum, uint8_t *parray[])
{
    if(pContrldata->pStartPtr   == NULL) return 0x11;
    if(pContrldata->pEndPtr     == NULL) return 0x22;
    if(pContrldata->n           == 0x00) return 0x33;

    if(elNum >= pContrldata->n) (elNum = (pContrldata->n - 1));

    MemoryMember_t *pMyEle;
    uint8_t i;

    pMyEle = pContrldata->pStartPtr;
    for(i=0; i<elNum; i++)
    {
        pMyEle = pMyEle->pNext;
    }

    for(i=0; i<pContrldata->contentSize; i++)
    {
        *parray[i] = pMyEle->mydata[i];
        printf("%c ",pMyEle->mydata[i]);
    }
}
//============================================================================

/*****************************************************************************
* name  - RemoveAndGetFirst
* breaf - This function remove and return member from Head
* in    - Pointer to global data wchitch contains taill and head of pointers
* in    - Data to put inside memory member
* ret   - uin64_t data of head object content
******************************************************************************/
uint64_t RemoveAndGetFirst(MallocControlData_t* pContrldata)
{
     // 1. Lista jest pusta. Oba wskaźniki pokauzją na zero.
    if((pContrldata->pStartPtr == NULL)||(pContrldata->n == 0x00))
    {
        printf("\n !!! Brak obiektow !!! \n");
        return 0x00;
    }

    MemoryMember_t *pNew, *pOld;
    uint64_t retVal;
    uint64_t* p64;

    // 2. zdejmowanie poprzedniego wzkaźnika.
    pOld = pContrldata->pStartPtr;
    pNew = pOld->pNext;

    // 3. Zwracanie usuwanej wartości.
    retVal  = *((uint64_t*)(pOld->mydata));

    // 4. Wyświetlanie usuwanej wartości.
    printf("\n Memory to free(0x%x) \n", pOld);

    if((pContrldata->pStartPtr == pContrldata->pEndPtr)||(pContrldata->n == 0x01))
    {   // 4. Jesli został tylko jeden obiekt.
        free((MemoryMember_t*)(pOld));
        pContrldata->pStartPtr  = NULL;
        pContrldata->pEndPtr    = NULL;
        pContrldata->n = 0x00;
        printf("Usuniety ostatni obiekt!!! \n");
    }
    else
    {   // 5. Zostały conajmniej 2 obiekty.
        pContrldata->pStartPtr = pNew;
        free((MemoryMember_t*)(pOld));
        pContrldata->n = pContrldata->n - 0x01;
    }
    return retVal;
}
//============================================================================


/*****************************************************************************
* name  - RemoveAndGetLast
* breaf - This function remove and return member from taill
* in    - Pointer to global data wchitch contains taill and head of pointers
* in    - Data to put inside memory member
* ret   - Data of taill object content
******************************************************************************/
uint64_t RemoveAndGetLast(MallocControlData_t* pContrldata)
{
     // 1. Lista jest pusta. Oba wskaźniki pokauzją na zero.
    if((pContrldata->pStartPtr == NULL)||(pContrldata->n == 0x00))
    {
        printf("\n Brak obiektow!! \n");
        return 0x00;
    }  

    MemoryMember_t *pNew, *pOld;
    uint64_t retVal;
    uint64_t* p64;

    // 2. zdejmowanie poprzedniego wzkaźnika.
    pOld = pContrldata->pEndPtr;
    pNew = pOld->pPrev;

    // 3. Zwracanie usuwanej wartości.
    retVal  = *((uint64_t*)(pOld->mydata));

    // 4. Wyświetlanie usuwanej wartości.
    printf("\n Memory to free(0x%x) \n", pOld);

    // 3. Jesli został tylko jeden obiekt.
    if((pContrldata->pStartPtr == pContrldata->pEndPtr)||(pContrldata->n == 0x01))
    {
        free((MemoryMember_t*)(pOld));
        pContrldata->pStartPtr  = NULL;
        pContrldata->pEndPtr    = NULL;
        pContrldata->n = 0x00;
        printf("Usuniety ostatni obiekt!!! \n");
    }
    else
    {   // 4. Zostały conajmniej 2 obiekty.
        pContrldata->pEndPtr = pNew;
        free((MemoryMember_t*)(pOld));
        pContrldata->n       = pContrldata->n - 0x01;
    }
    return retVal;
}
//============================================================================

/*****************************************************************************
* name  - RemoveAllObj
* breaf - This function removes all elements from memory;
* in    - Pointer to global data wchitch contains taill and head of pointers
* in    - Print format of memeber data
* ret   - If object do not exist return value type
******************************************************************************/
uint8_t RemoveAllObj(MallocControlData_t* pContrldata, uint8_t objsize)
{
    uint8_t i,n;
    MemoryMember_t *pNewHead, *pOldHead; 

    // Check invalid condition
    if(pContrldata->pStartPtr   == NULL) return 0x11;
    if(pContrldata->pEndPtr     == NULL) return 0x22;
    if(pContrldata->n           == 0x00) return 0x33;

    /*  Two exit condition:
    *   pContrldata->n == 1
    *   pContrldata->pStartPtr == pContrldata->pEndPtr */  
    n = pContrldata->n - 1;
    for(i=0; i<n; i++)
    {
        if(pContrldata->pStartPtr == pContrldata->pEndPtr) break;

        pOldHead = pContrldata->pEndPtr;
        pNewHead = pOldHead->pPrev;
        pContrldata->pEndPtr = pNewHead;
        pContrldata->n--;
        free(pOldHead);
    }

    // Remove last element;
    //printf("Start ptr = %x \n", pContrldata->pStartPtr);
    //printf("End   ptr = %x \n", pContrldata->pEndPtr);
    pOldHead = pContrldata->pEndPtr;
    free(pOldHead);
    pContrldata->n = 0x00;
    pContrldata->pStartPtr  = NULL;
    pContrldata->pEndPtr    = NULL;

    return 0x00;
}
//============================================================================

/*****************************************************************************
* name  - PrintFromDynamicArray
* breaf - This function print array data member
* in    - Pointer to global data wchitch contains taill and head of pointers
* in    - Print format of memeber data
* ret   - void
******************************************************************************/
void PrintFromDynamicArray(MallocControlData_t* pContrldata, uint8_t printType)
{
    uint8_t i,n;
    MemoryMember_t* pMember;

    pMember = pContrldata->pStartPtr;
    if(printType == PRINT_TYPE_01)
    {
        printf("\n--------------------------------\n");
        for(n=0; n<pContrldata->n; n++)
        {
            for(i=0; i<DATA_LEN; i++)
            {
                printf("| %c |", pMember->mydata[i]);
            }
            pMember = pMember->pNext;
            printf("\n--------------------------------\n");
        }
    }
    else if((printType == PRINT_TYPE_02)&&(pMember != NULL))
    {   n = 0x00;
        printf("\n--------------------------------\n");
        while((pMember != NULL)&&(n < pContrldata->n))
        {   n = n + 0x01;
            for(i=0; i<DATA_LEN; i++)
            {
                printf("| [%x]: %c |", i,pMember->mydata[i]);
            }
            printf(" ADDR: %x", pMember);
            pMember = pMember->pNext;
            printf("\n--------------------------------\n");
        }
    }
    else if(printType == PRINT_TYPE_03)
    {
        uint64_t* pTemp;
        printf("\n--------------------------------\n");
        for(n=0; n<pContrldata->n; n++)
        {
            pTemp = (uint64_t*)((pMember->mydata));
            printf("uint64_t: %x | ADDR: %x",*pTemp, pTemp);
            pMember = pMember->pNext;
            printf("\n--------------------------------\n");
        }
    }
    else{;}

    return;
}
//============================================================================

uint8_t DynamicStackTest1(uint8_t exit)
{   
    if(exit == 0xFF)
        return 0xFF;

    //char myData[DATA_LEN];
    uint64_t myData;
    MallocControlData_t Contrldata = {NULL, NULL, 0x00};
    
    uint64_t tVal;

    //myData[0] = '1'; myData[1] = '1';
    //myData[2] = '1'; myData[3] = '1';
    myData = 0x12345678;
    AddFirstItem(&Contrldata, (char*)(&myData));

    //myData[0] = '2'; myData[1] = '2'; 
    //myData[2] = '2'; myData[3] = '2';
    myData = 0x9ABCDEF0;
    AddItemToEnd(&Contrldata, (char*)(&myData));
    //AddItemOnFront(&Contrldata, myData);    

    //myData[0] = '3'; myData[1] = '3'; 
    //myData[2] = '3'; myData[3] = '3';
    myData = 0x87654321;
    //AddItemToEnd(&Contrldata, myData);  
    AddItemOnFront(&Contrldata, (char*)(&myData));    

    //myData[0] = '4'; myData[1] = '4'; 
    //myData[2] = '4'; myData[3] = '4';
    //AddItemToEnd(&Contrldata, myData);  
    //AddItemOnFront(&Contrldata, myData); 

    /*
    tVal = RemoveAndGetFirst(&Contrldata);
    printf("Val ret: %x \n",tVal);
    */
    printf("Object amout: %x \n", Contrldata.n);
    PrintFromDynamicArray(&Contrldata, PRINT_TYPE_03);

    
    tVal = RemoveAndGetLast(&Contrldata);
    printf(" Val ret: %x \n",tVal);
    PrintFromDynamicArray(&Contrldata, PRINT_TYPE_03);

    tVal = RemoveAndGetLast(&Contrldata);
    printf(" Val ret: %x \n",tVal);
    PrintFromDynamicArray(&Contrldata, PRINT_TYPE_03);

    tVal = RemoveAndGetLast(&Contrldata);
    printf(" Val ret: %x \n",tVal);
    PrintFromDynamicArray(&Contrldata, PRINT_TYPE_03);

    tVal = RemoveAndGetLast(&Contrldata);
    printf(" Val ret: %x \n",tVal);
    PrintFromDynamicArray(&Contrldata, PRINT_TYPE_03);

    return 0;
}

uint8_t DynamicStackTest2(uint8_t exit)
{   
    if(exit == 0xFF)
        return 0xFF;

    char myData[DATA_LEN];
    MallocControlData_t Contrldata = {NULL, NULL, 0x00};

    uint8_t temp;
    
    uint64_t tVal;

    myData[0] = '0'; myData[1] = '0';
    myData[2] = '0'; myData[3] = '1';
    AddFirstItem(&Contrldata, myData);

    myData[0] = '0'; myData[1] = '0'; 
    myData[2] = '0'; myData[3] = '2';
    AddItemToEnd(&Contrldata, myData);
    //AddItemOnFront(&Contrldata, myData);    

    myData[0] = '0'; myData[1] = '0'; 
    myData[2] = '0'; myData[3] = '3';
    AddItemToEnd(&Contrldata, myData);  
    //AddItemOnFront(&Contrldata, myData);    

    myData[0] = '0'; myData[1] = '0'; 
    myData[2] = '0'; myData[3] = '4';
    AddItemToEnd(&Contrldata, myData);  
    //AddItemOnFront(&Contrldata, myData); 

    //temp = GetElement(&Contrldata, 0, myData);

    printf("First object: \n");
    printf("Ret: %c-%c-%c-%c \n",myData[0], myData[1], myData[2], myData[3]);
    
    //temp = GetElement(&Contrldata, 3, myData);
    printf("Second object: \n");
    printf("Ret: %c-%c-%c-%c \n",myData[0], myData[1], myData[2], myData[3]);
    
    temp = RemoveAllObj(&Contrldata, DATA_LEN);

    return temp;
}



