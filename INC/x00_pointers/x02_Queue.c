#include "x02_Queue.h"
#ifdef _X02_INCLUDE_QUEUE_H

static void _MoveData(char* pDST, char* pSRC, int dataLenght)
{
    int i;
    for(i=0; i<dataLenght; i++)
    {
        *(pDST + i) = *(pSRC + i);
    }
}

char QueueInit( queueMenagment_t* pQueue,   elm_data_t* pElem)
{
    queueEl_t* pNew = (queueEl_t*)malloc(sizeof(queueEl_t));
    pNew->pNEXT = pNew;
    pNew->pPREV = pNew;

    pQueue->pHead = pNew;
    pQueue->pTail = pNew;
    pQueue->dAmount = 1;

    _MoveData((char*)&(pNew->element), (char*)&(pElem), sizeof(elm_data_t));

    return STATUS_SUCES;
}

char QueuePut(queueMenagment_t* pQueue,     elm_data_t* pElem)
{
    if(pQueue->dAmount >= QUEUE_TWO_ATLEAST)
    {
        queueEl_t* pNew = (queueEl_t*)malloc(sizeof(queueEl_t));

        pNew->pNEXT = NULL;
        pNew->pPREV = pQueue->pHead;

        pQueue->pHead = pNew;
        pQueue->dAmount++;

        _MoveData((char*)&(pNew->element), (char*)&(pElem), sizeof(elm_data_t));

        return STATUS_SUCES;
    }
    else
        return STATUS_ERROR;
}

char QueueGet(queueMenagment_t* pQueue,     elm_data_t* pElem)
{
    if(pQueue->dAmount >= QUEUE_ONE_ELEMENT)
    {
        _MoveData((char*)&(pQueue->pHead), (char*)(pElem), sizeof(elm_data_t));
        return STATUS_SUCES;
    }
    else    
        return STATUS_ERROR;
}


char QueueRemove(queueMenagment_t* pQueue,  elm_data_t* pElem)
{
    if(pQueue->dAmount == QUEUE_EMPTY)
    {
        return STATUS_ERROR;
    }
    else if(pQueue->dAmount == QUEUE_ONE_ELEMENT)
    {
        pQueue->pHead = NULL;
        pQueue->pTail = NULL;
        pQueue->dAmount = QUEUE_EMPTY;
        free(pQueue->pHead);

        return STATUS_SUCES;
    }
    else // pQueue->dAmount >= QUEUE_TWO_ATLEAST
    {
        return STATUS_SUCES;
    }
}

#endif // _X02_INCLUDE_QUEUE_H