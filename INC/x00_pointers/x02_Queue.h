#include "_x00_include.h"
#ifdef _X02_INCLUDE_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_EMPTY         0x00
#define QUEUE_ONE_ELEMENT   0x01
#define QUEUE_TWO_ATLEAST   0x02

#define STATUS_SUCES 0x00
#define STATUS_ERROR 0xFF

typedef struct 
{
    long lData1;
    long lData2;
}elm_data_t;

typedef struct queueEl_t
{
    struct queueEl_t* pNEXT;
    struct queueEl_t* pPREV;
    elm_data_t element;
}queueEl_t;

typedef struct 
{
    queueEl_t* pHead;
    queueEl_t* pTail;
    long lAmount;
}queueMenagment_t;

char QueueInit(queueMenagment_t* pQueue,    elm_data_t* pElem);
char QueuePut(queueMenagment_t* pQueue,     elm_data_t* pElem);
char QueueGet(queueMenagment_t* pQueue,     elm_data_t* pElem);
char QueueRemove(queueMenagment_t* pQueue,  elm_data_t* pElem);

#endif // _X02_INCLUDE_QUEUE_H