#include "_x00_include.h"
#ifdef _X10_INCLUDE_TEST_H

    #ifdef _X01_INCLUDE_LINKED_LIST_H
        #include "x01_Linked_list.h"

        void PrintInfoList(listInfo_t* plistInfo);

        void CALL_TestList1(void);
        void CALL_TestList2(void);
        void CALL_TestList3(void);

        void CALL_TestList4(void);
        void CALL_TestList5(void);

        void CALL_TestList6(void);

    #endif 

    #ifdef _X02_INCLUDE_QUEUE_H
        #include "x02_Queue.h"

        void PrintInfoQueue(queueEl_t* pQueElems);
        void CALL_TestQueue1(void);

    #endif 

    #ifdef _X03_INCLUDE_STACK_H
        #include "x03_Stack.h"
    
    #endif 

#endif 