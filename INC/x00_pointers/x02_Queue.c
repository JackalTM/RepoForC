#include "x02_Queue.h"
#ifdef _X02_INCLUDE_QUEUE_H

/****************************************************************************************************
 * @name    
 * @brief   
 * 
 * @param[in]    
 * @param[in]   
 * 
 * @note           
 * @return      
*/
//===================================================================================================

/****************************************************************************************************
 * @name        _MoveData
 * @brief       Move any type of data from to destination pointer
 * 
 * @param[in]   pDST Destination pointer  
 * @param[in]   pSRC Source pointer 
 * @param[in]   dataLenght Lenght of data 
 * 
 * @note        Staric function
 * @return      void
*/
static void _MoveData(char* pDST, char* pSRC, int dataLenght)
{
    int i;
    for(i=0; i<dataLenght; i++)
    {
        *(pDST + i) = *(pSRC + i);
    }
}
//===================================================================================================

/****************************************************************************************************
 * @name        QueueInit
 * @brief       Init function for Queue
 * 
 * @param[in]   pQueue Pointer of type queueMenagment_t* for Queue menagment global data struture.
 * @param[in]   pElem Pointer of type elm_data_t* for input first element to queue
 * 
 * @note           
 * @return      Status of operation of type char
*/
char QueueInit(queueMenagment_t* pQueue,   elm_data_t* pElem)
{
    queueEl_t* pNew = (queueEl_t*)malloc(sizeof(queueEl_t));
    pNew->pNEXT = pNew;
    pNew->pPREV = pNew;

    pQueue->pHead = pNew;
    pQueue->pTail = pNew;
    pQueue->lAmount = QUEUE_ONE_ELEMENT;

    _MoveData((char*)&(pNew->element), (char*)&(pElem), sizeof(elm_data_t));

    return STATUS_SUCES;
}
//===================================================================================================

/****************************************************************************************************
 * @name        QueuePut
 * @brief       Add another element to the top of the head
 * 
 * @param[in]   pQueue Pointer to the menagment structure 
 * @param[in]   pElem Pointer to the new element 
 * 
 * @note           
 * @return      Char - status of the operation
*/
char QueuePut(queueMenagment_t* pQueue,     elm_data_t* pElem)
{
    if(pQueue->lAmount >= QUEUE_TWO_ATLEAST)
    {
        queueEl_t* pNew = (queueEl_t*)malloc(sizeof(queueEl_t));

        pNew->pNEXT = NULL;
        pNew->pPREV = pQueue->pHead;

        pQueue->pHead = pNew;
        pQueue->lAmount = pQueue->lAmount + 1;

        _MoveData((char*)&(pNew->element), (char*)&(pElem), sizeof(elm_data_t));

        return STATUS_SUCES;
    }
    else
        return STATUS_ERROR;
}
//===================================================================================================

/****************************************************************************************************
 * @name        QueueGet
 * @brief       Get element from head of the queue
 * 
 * @param[in]   pQueue Pointer to the menagment structure 
 * @param[in]   pElem Pointer to return element data
 * 
 * @note           
 * @return      Status of the operation
*/
char QueueGet(queueMenagment_t* pQueue,     elm_data_t* pElem)
{
    if(pQueue->lAmount >= QUEUE_ONE_ELEMENT)
    {
        _MoveData((char*)&(pQueue->pHead), (char*)(pElem), sizeof(elm_data_t));
        return STATUS_SUCES;
    }
    else    
        return STATUS_ERROR;
}
//===================================================================================================

/****************************************************************************************************
 * @name        QueueRemove
 * @brief       Get element from head of the queue and remove
 * 
 * @param[in]   pQueue Pointer to the menagment structure
 * @param[in]   pElem Pointer to return element data
 * 
 * @note           
 * @return      Status of the operation
*/
char QueueRemove(queueMenagment_t* pQueue,  elm_data_t* pElem)
{
    if(pQueue->lAmount == QUEUE_EMPTY)
    {
        return STATUS_ERROR;
    }
    else if(pQueue->lAmount == QUEUE_ONE_ELEMENT)
    {
        pQueue->pHead = NULL;
        pQueue->pTail = NULL;
        pQueue->lAmount = QUEUE_EMPTY;
        free(pQueue->pHead);

        return STATUS_SUCES;
    }
    else // pQueue->lAmount >= QUEUE_TWO_ATLEAST
    {
        return STATUS_SUCES;
    }
}
//===================================================================================================

#endif // _X02_INCLUDE_QUEUE_H