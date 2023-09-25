#include "x10_TEST.h"
#ifdef _X10_INCLUDE_TEST_H


    #ifdef _X01_INCLUDE_LINKED_LIST_H
    
        void PrintInfoList(listInfo_t* plistInfo)
        {
            printf("Amount of elements : %d \n", plistInfo->iAmount);
            printf("ADDR pHead:= %x \n", plistInfo->pHead);
            printf("ADDR pTail:= %x \n --- \n", plistInfo->pTail);
        }

        void CALL_TestList1(void)
        {
            listItem_t* pOld;
            listItem_t* pNew;
            listItem_t* pTemp;
            int i;

            pNew = (listItem_t*)malloc(sizeof(listItem_t));
            pNew->pNEXT = NULL;
            pNew->pPREV = NULL;
            pNew->iData = 0;
            //pNew->datOK = 'A';

            //printf("DATA= %x | datOK= %c \n", pNew->lData, pNew->datOK);
            printf("ADDR NEW= %x \n", 0x0);
            printf("ADDR OLD= %x \n --------------------- \n", 0x0);

            for(i=1; i<LIST_AMOUNT; i++)
            {
                pOld = pNew;
                pNew = (listItem_t*)malloc(sizeof(listItem_t));
                
                pOld->pNEXT = pNew;
                pNew->pPREV = pOld;
                pNew->pNEXT = NULL;

                pNew->iData = i;
                //pNew->datOK = pOld->datOK + 1;

                //printf("DATA= %x | datOK= %c \n", pNew->iData, pNew->datOK);
                printf("ADDR NEW= %x \n", pNew);
                printf("ADDR OLD= %x \n --------------------- \n", pOld);
            }

            pTemp = pNew;
            for(i=0; i<LIST_AMOUNT; i++)
            {
                pTemp = pTemp->pPREV;
                //printf("DATA= %x | datOK= %c \n", pTemp->iData, pTemp->datOK);
                printf("ADDR pNEXT= %x \n", pTemp->pNEXT);
                printf("ADDR= %x \n", pTemp);
                printf("ADDR pPREV= %x \n --------------------- \n", pTemp->pPREV); 
                free(pTemp);
            }
            
        }

        void CALL_TestList2(void)
        {
            listInfo_t ListInfo;
            int i;
            int num;

            num = 0;
            ListInit((listInfo_t*)&ListInfo, &num);
            printf("Currenct head element := %d \n", num);
            printf("Current head := %x \n -- \n", ListInfo.pHead);

            for(i=1; i<4; i++)
            {
                ListPutHead((listInfo_t*)&ListInfo, &i);
                ListGetHead((listInfo_t*)&ListInfo, &num);
                printf("Currenct head element := %d \n", num);
                printf("Current head := %x \n -- \n", ListInfo.pHead);
            }
        }

        void CALL_TestList3(void)
        {
            listInfo_t ListInfo;
            int i;
            int num;

            num = 0;
            ListInit((listInfo_t*)&ListInfo, &num);
            printf("Currenct tail element := %d \n", num);
            printf("Current tail := %x \n -- \n", ListInfo.pTail);

            for(i=1; i<4; i++)
            {
                ListPutTail((listInfo_t*)&ListInfo, &i);
                ListGetTail((listInfo_t*)&ListInfo, &num);
                printf("Currenct tail element := %d \n", num);
                printf("Current tail := %x \n -- \n", ListInfo.pTail);
            }
        }

        void CALL_TestList4(void)
        {
            listInfo_t ListInfo;
            int i;
            int num;

            printf("Test head \n --- \n");

            num = 0;
            ListInit((listInfo_t*)&ListInfo, &num);
            for(i=1; i<4; i++)
            {
                ListPutHead((listInfo_t*)&ListInfo, &i);
            }

            for(i=0;i<4; i++)
            {
                ListGetHead((listInfo_t*)&ListInfo, &num);

                PrintInfoList((listInfo_t*)&ListInfo);

                ListRemoveHead((listInfo_t*)&ListInfo, &num);
            }

            PrintInfoList((listInfo_t*)&ListInfo);
        }

        void CALL_TestList5(void)
        {
            listInfo_t ListInfo;
            int i;
            int num;

            printf("Test tail \n --- \n");

            num = 0;
            ListInit((listInfo_t*)&ListInfo, &num);
            for(i=1; i<4; i++)
            {
                ListPutTail((listInfo_t*)&ListInfo, &i);
            }

            for(i=0;i<4; i++)
            {
                ListGetTail((listInfo_t*)&ListInfo, &num);

                PrintInfoList((listInfo_t*)&ListInfo);

                ListRemoveTail((listInfo_t*)&ListInfo, &num);
            }

            PrintInfoList((listInfo_t*)&ListInfo);
        }

        void CALL_TestList6(void)
        {
            listInfo_t ListInfo;
            int i;
            int num;
            int max = 8;

            num = 0;
            ListInit((listInfo_t*)&ListInfo, &num);
            for(i=1; i<max; i++)
            {
                ListPutHead((listInfo_t*)&ListInfo, &i);
            }

            for(i=0; i<max; i++)
            {
                printf("================ \n");
                ListGetElement((listInfo_t*)&ListInfo, &num, i);
                printf("Element %i is %d \n", i, num);
            }
        }
        
    #endif 

    #ifdef _X02_INCLUDE_QUEUE_H

        void PrintInfoQueue(queueEl_t* pQueElems)
        {
            printf("ADDR pNEXT:= %x \n", pQueElems->pNEXT);
            printf("ADDR pPREV:= %x \n", pQueElems->pPREV);
            printf("Element D1:= %d \n", pQueElems->element.lData1);
            printf("Element D2:= %d \n", pQueElems->element.lData2);
        }

        void PrintInfoAll(queueMenagment_t* pQueMenag)
        {
            printf("ADDR pHead:= %x \n", pQueMenag->pHead);
            printf("ADDR pTail:= %x \n", pQueMenag->pTail);
            printf("Elements n:= %d \n", pQueMenag->lAmount);
        }

        void CALL_TestQueue1(void)
        {
            queueMenagment_t menagmentData;
            elm_data_t interData;
            int i;

            interData.lData1 = -1;
            interData.lData2 = -1;
            QueueInit((queueMenagment_t*)&menagmentData, (elm_data_t*)&interData);

            for(i=0; i<TEST_AMOUNT; i++)
            {
                printf("Test for: \n");
                interData.lData1 = i;
                interData.lData2 = i;
                QueuePut((queueMenagment_t*)&menagmentData, (elm_data_t*)&interData);   
            }

            QueueGet(&menagmentData, &interData);
            PrintInfoQueue((queueEl_t*)&(menagmentData.pHead));

            PrintInfoAll(&menagmentData);
        }
    
    #endif 

    #ifdef _X03_INCLUDE_STACK_H

    
    #endif 

#endif // _X01_INCLUDE_TEST_H