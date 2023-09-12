#include "x01_Linked_list.h"
#ifdef _X01_INCLUDE_LINKED_LIST_H

/******************************************************************************************************
 * @name        ListInit
 * @brief       ...
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * 
 * @note        OK
 * @return      Status of the operation
*/
char ListInit(listInfo_t* plistInfo, int* piElement)
{
    listItem_t* pNew = (listItem_t*)malloc(sizeof(listItem_t));

    pNew->iData = *piElement;
    pNew->pNEXT = pNew;
    pNew->pPREV = pNew;

    plistInfo->iAmount = 0x01;
    plistInfo->pHead = pNew;
    plistInfo->pTail = pNew;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        ListPutHead
 * @brief       ...
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * @param[in]   piElement Pointer to new element.
 * 
 * @note        OK
 * @return      Status of the operation
*/
char ListPutHead(listInfo_t* plistInfo, int* piElement)
{
    if((plistInfo->pHead != NULL) && (plistInfo->pTail != NULL))
    {
        listItem_t* pNew = (listItem_t*)malloc(sizeof(listItem_t));
        listItem_t* pOld = plistInfo->pHead;

        pOld->pNEXT = pNew;
        pNew->pPREV = pOld;

        pNew->iData = *piElement;
        plistInfo->iAmount = plistInfo->iAmount + 1;
        plistInfo->pHead = pNew;

        return OPERATION_SUCESS;
    }
    else
        OPERATION_FAULT;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        ListInit
 * @brief       ...
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * 
 * @note        OK
 * @return      Status of the operation
*/
char ListPutTail(listInfo_t* plistInfo, int* piElement)
{
    if((plistInfo->pHead != NULL) && (plistInfo->pTail != NULL))
    {
        listItem_t* pNew = (listItem_t*)malloc(sizeof(listItem_t));
        listItem_t* pOld = plistInfo->pTail;

        pOld->pPREV = pNew;
        pNew->pNEXT = pOld;

        pNew->iData = *piElement;
        plistInfo->iAmount = plistInfo->iAmount + 1;
        plistInfo->pTail = pNew;

        return OPERATION_SUCESS;
    }
    else
        return OPERATION_FAULT;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        ListGetHead
 * @brief       Get head element from list
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * 
 * @note        OK
 * @return      Status of the operation
*/
char ListGetHead(listInfo_t* plistInfo, int* piElement)
{
    if((plistInfo->iAmount > 0) && (plistInfo->pHead != NULL))
    {
        listItem_t* pHead = plistInfo->pHead;
        *piElement = pHead->iData;

        return OPERATION_SUCESS;
    }
    else
        return OPERATION_FAULT;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        ListGetTail
 * @brief       Get tail element from list
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * 
 * @note        OK
 * @return      Status of the operation
*/
char ListGetTail(listInfo_t* plistInfo, int* piElement)
{
    if((plistInfo->iAmount > 0) && (plistInfo->pTail != NULL))
    {
        listItem_t* pTail = plistInfo->pTail;
        *piElement = pTail->iData; 

        return OPERATION_SUCESS;
    }
    else
        return OPERATION_FAULT;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        _ListGetMid
 * @brief       Get specyfic element from List
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * @param[in]   n Number from index n list
 * @param[in]   piElement Pointer to return element
 * 
 * @note        OK
 * @return      Status of the operation
*/
static char _ListGetMid(listInfo_t* plistInfo, int* piElement, int index)
{
    if(index < plistInfo->iAmount)
    {
        int i;
        int temp;
        listItem_t* pElement; 

        if((index * 2) <  plistInfo->iAmount)
        {
            pElement = plistInfo->pTail;
            for(i=0; i < index; i++)
            {
                pElement = pElement->pNEXT;
            }
            temp = i;
        }
        else
        {
            pElement = plistInfo->pHead;
            for(i=0; i < index; i++)
            {
                pElement = pElement->pPREV;
            }
            temp = i;
        }

        *piElement = temp;
        return OPERATION_SUCESS;
    }
    else
        return OPERATION_FAULT;
}
//=====================================================================================================

/******************************************************************************************************
 * @name        ListGetElement
 * @brief       Get specyfic element from List
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * @param[in]   n Number from index n list
 * @param[in]   piElement Pointer to return element
 * 
 * @note        OK
 * @return      Status of the operation
*/
char ListGetElement(listInfo_t* plistInfo, int* piElement, int n)
{
    printf("index:= %d \n", n);
    if(n == FIRST_ELEMENT)
    {   
        return ListGetTail(plistInfo, piElement); 
    }
    else if(n == LAST_ELEMENT)
    {   
        return ListGetHead(plistInfo, piElement); 
    }
    else
    {   
        return _ListGetMid(plistInfo, piElement, n); 
    }
}
//=====================================================================================================

/******************************************************************************************************
 * @name        _ListRemoveLastHead
 * @brief       Head of the list is removed and memory is free() when last element is present
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * 
 * @note        OK
 * @return      Status of the operation
*/
static char _ListRemoveLastHead(listInfo_t* plistInfo)
{
    if((plistInfo->iAmount == 0x01) && (plistInfo->pHead == plistInfo->pTail))
    {
        free(plistInfo->pHead);

        plistInfo->iAmount = 0x00;
        plistInfo->pHead = NULL;
        plistInfo->pTail = NULL;

        return OPERATION_SUCESS;
    } 
    else
        return OPERATION_FAULT;
}
/******************************************************************************************************
 * @name        _ListRemoveHeadMore
 * @brief       Head of the list is removed and memory is free() when at least two elements
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * 
 * @note        OK
 * @return      Status of the operation
*/
static char _ListRemoveHeadMore(listInfo_t* plistInfo)
{
    if((plistInfo->iAmount >= 0x02) && (plistInfo->pHead != plistInfo->pTail))
    {
        listItem_t* pToRemove;
        listItem_t* pNewHead;

        pToRemove = plistInfo->pHead;
        pNewHead = pToRemove->pPREV;
        pNewHead->pNEXT = NULL;

        plistInfo->pHead = pNewHead;
        plistInfo->iAmount = plistInfo->iAmount - 1;

        free(pToRemove);

        return OPERATION_SUCESS;
    }
    else
        return OPERATION_FAULT;
}
/******************************************************************************************************
 * @name        ListRemoveHead
 * @brief       Head of the list is removed and memory is free()
 *              This function use two private
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * 
 * @note        OK
 * @return      Status of the operation
*/
char ListRemoveHead(listInfo_t* plistInfo, int* piElement)
{
    if(plistInfo->iAmount >=0x02)
        return _ListRemoveHeadMore(plistInfo);
    else
       return  _ListRemoveLastHead(plistInfo);
}
//=====================================================================================================

/******************************************************************************************************
 * @name        _ListRemoveLastTail
 * @brief       Tail of the list is removed and memory is free() when last element is present
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * 
 * @note        OK
 * @return      Status of the operation
*/
static char _ListRemoveLastTail(listInfo_t* plistInfo)
{
    if((plistInfo->iAmount == 0x01) && (plistInfo->pHead == plistInfo->pTail))
    {
        free(plistInfo->pTail);

        plistInfo->iAmount = 0x00;
        plistInfo->pHead = NULL;
        plistInfo->pTail = NULL;

        return OPERATION_SUCESS;
    } 
    else
        return OPERATION_FAULT;
}
/******************************************************************************************************
 * @name        _ListRemoveTailMore
 * @brief       Tail of the list is removed and memory is free() when at least two elements
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * 
 * @note        OK
 * @return      Status of the operation
*/
static char _ListRemoveTailMore(listInfo_t* plistInfo)
{
    if((plistInfo->iAmount >= 0x02) && (plistInfo->pHead != plistInfo->pTail))
    {
        listItem_t* pToRemove;
        listItem_t* pNewTail;

        pToRemove = plistInfo->pTail;
        pNewTail = pToRemove->pNEXT;
        pNewTail->pPREV = NULL;

        plistInfo->pTail = pNewTail;
        plistInfo->iAmount = plistInfo->iAmount - 1;

        free(pToRemove);

        return OPERATION_SUCESS;
    }
    else
        return OPERATION_FAULT;
}
/******************************************************************************************************
 * @name        ListRemoveTail
 * @brief       Tail of the list is removed and memory is free()
 *              This function use two private
 * 
 * @param[in]   plistInfo Pointer to main menagment structure.
 * 
 * @note        OK
 * @return      Status of the operation
*/
char ListRemoveTail(listInfo_t* plistInfo, int* piElement)
{
    if(plistInfo->iAmount >=0x02)
        return _ListRemoveTailMore(plistInfo);
    else
       return  _ListRemoveLastTail(plistInfo);
}
//=====================================================================================================

#endif // _X01_INCLUDE_LINKED_LIST_H