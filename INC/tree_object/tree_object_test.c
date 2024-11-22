#include "tree_object_test.h"
#ifdef _TREE_OBJECT_TEST_H

/****************************************************************************************************
 * @name        CALL_treeTest01  
 * @brief       Call for test tree object  
 * 
 * @note           
 * @return      void    
*/
void CALL_treeTest01(void)
{
    // 1 + 2 * 3
    treeElemControl_t treeElemControl;
    treeElement_t obj1, obj2, obj3, obj4, obj5;

    obj1 = TreeObjCreateValue(1);
    obj2 = TreeObjCreateOperation(TREE_OBJ_OPR_ADD);
    obj3 = TreeObjCreateValue(2);
    obj4 = TreeObjCreateOperation(TREE_OBJ_OPR_MUL);
    obj5 = TreeObjCreateValue(3);

    obj2.pTreeElemLeft = (treeElement_t*)&obj1;
    obj2.pTreeElemRigh = (treeElement_t*)&obj4;

    obj4.pTreeElemLeft = (treeElement_t*)&obj3;
    obj4.pTreeElemRigh = (treeElement_t*)&obj5;

    treeElemControl.nCalls  = 0x00;
    treeElemControl.nMAX    = MAX_AMOUNT_OF_CALLS;
    treeElemControl.exitOnCall = 0x00;
    TreeObjPrintAllTree((treeElement_t*)&obj2, &treeElemControl, 0x00);

    printf("\n -- Amount of self calls:= %x \n", treeElemControl.nCalls);
}
//===================================================================================================

/****************************************************************************************************
 * @name        CALL_treeTest02  
 * @brief       Call for test tree object  
 * 
 * @note           
 * @return      void    
*/
void CALL_treeTest02(void)
{
    // 1 + 2 * 3
    treeElemControl_t treeElemControl;
    treeElement_t obj1, obj2, obj3, obj4, obj5;

    obj1 = TreeObjCreateValue(1) ;
    obj2 = TreeObjCreateOperation(TREE_OBJ_OPR_ADD);
    obj3 = TreeObjCreateValue(2);
    obj4 = TreeObjCreateOperation(TREE_OBJ_OPR_MUL);
    obj5 = TreeObjCreateValue(3);

    obj2.pTreeElemLeft = (treeElement_t*)&obj1;
    obj2.pTreeElemRigh = (treeElement_t*)&obj4;

    obj4.pTreeElemLeft = (treeElement_t*)&obj3;
    obj4.pTreeElemRigh = (treeElement_t*)&obj5;

    treeElemControl.nCalls  = 0x00;
    treeElemControl.nMAX    = MAX_AMOUNT_OF_CALLS;
    treeElemControl.exitOnCall = 0x00;
    TreeObjPrintAllTree(&obj2, &treeElemControl, 0x00);

    treeElemControl.nCalls  = 0x00;
    treeElemControl.nMAX    = MAX_AMOUNT_OF_CALLS;
    treeElemControl.exitOnCall = 0x00;
    TreeObjEvaluateTree(&obj2, &treeElemControl);

    printf("\n\n After calculation \n");

    treeElemControl.nCalls  = 0x00;
    treeElemControl.nMAX    = MAX_AMOUNT_OF_CALLS;
    treeElemControl.exitOnCall = 0x00;
    TreeObjPrintAllTree(&obj2, &treeElemControl, 0x00);

    printf("\n -- Amount of self calls:= %2x \n", treeElemControl.nCalls);
}
//===================================================================================================

/****************************************************************************************************
 * @name        CALL_treeTest03  
 * @brief       Call for test tree object  
 * 
 * @note           
 * @return      void    
*/
void CALL_treeTest03(char inChar)
{
    char tempChar = inChar;
    char tempOperation = 0x00;

    if(tempChar == 0x00)
    {
        tempChar = 0xFF;
    }
    else if((tempChar >= '0') && (tempChar <= '9'))
    {
        tempChar = tempChar - '0';
    }
    else if((tempChar >= 'A') && (tempChar <= 'F'))
    {
        tempChar = tempChar - 0x37;
    }
    else if((tempChar >= 'a') && (tempChar <= 'f'))
    {
        tempChar = tempChar - 0x57;
    }
    else
    {// Opeator condition
        switch (inChar)
        {
            case '+':   tempOperation = 0xFF; break;
            case '-':   tempOperation = 0xFF; break;
            case '*':   tempOperation = 0xFF; break;
            case '/':   tempOperation = 0xFF; break;
            
            default:    tempChar = 0xFF;    break;
        }
    }

    if(tempOperation == 0xFF)
    {
        printf("---------- \n");
        printf("Input char:= %c \n", inChar);
        printf("Operation %x \n", inChar);
        printf("++++++++++ \n"); 
    }
    else
    {
        printf("---------- \n");
        printf("Input char:= %c \n", inChar);
        printf("Number %x \n", tempChar);
        printf("++++++++++ \n");  
    }
}
//===================================================================================================

/****************************************************************************************************
 * @name        CALL_treeTest04 
 * @brief       Call for test tree object  
 * 
 * @note           
 * @return      void    
*/
void CALL_treeTest04(char pArrArguments[])
{
    //"+12-34 "
    treeElemParse_t     treeElemParse;
    treeElement_t*      pRootTreeObj;

    treeElemParse.pStr  = pArrArguments;
    treeElemParse.idx   = 0x00;
    treeElemParse.nMax  = strlen(pArrArguments);

    printf("Input string: %s \n", pArrArguments);
    printf("strlen()= %x \n", treeElemParse.nMax);

    TreeObjParse_Alpha(&treeElemParse);
}
//===================================================================================================

/****************************************************************************************************
 * @name        CALL_treeTest05
 * @brief       Call for test tree object  
 * 
 * @note           
 * @return      void    
*/
void CALL_treeTest05(char pArrArguments[])
{
    //"+12-34 "
    treeElemControl_t   treeElemControl;
    treeElemParse_t     treeElemParse;
    treeElement_t*      pRootTreeObj;

    treeElemParse.pStr  = pArrArguments;
    treeElemParse.idx   = 0x00;
    treeElemParse.nMax  = strlen(pArrArguments);

    printf("Input string: %s \n", pArrArguments);
    printf("strlen()= %x \n", treeElemParse.nMax);

    TreeObjParse_Beta(&pRootTreeObj, &treeElemParse);

    treeElemControl.nCalls  = 0x00;
    treeElemControl.nMAX    = MAX_AMOUNT_OF_CALLS;
    treeElemControl.exitOnCall = 0x00;
    TreeObjPrintAllTree(pRootTreeObj, &treeElemControl, 0x00);

    treeElemControl.nCalls  = 0x00;
    treeElemControl.nMAX    = MAX_AMOUNT_OF_CALLS;
    treeElemControl.exitOnCall = 0x00;
    TreeObjEvaluateTree(pRootTreeObj, &treeElemControl);
    printf("| %s = %f \n", pArrArguments, pRootTreeObj->value);

    treeElemControl.nCalls  = 0x00;
    treeElemControl.nMAX    = MAX_AMOUNT_OF_CALLS;
    treeElemControl.exitOnCall = 0x00;
    TreeObjReliseAllMemory(pRootTreeObj, &treeElemControl);
}
//===================================================================================================

/****************************************************************************************************
 * @name        CALL_treeTest06
 * @brief       Call for test tree object  
 * 
 * @note        Call function for test functionality
 * @return      void    
*/
void CALL_treeTest06(char pArrArguments[])
{
    treeElemControl_t   treeElemControl;
    treeElemParse_t     treeElemParse;
    treeElement_t*      pRootTreeObj;

    treeElemParse.pStr  = pArrArguments;
    treeElemParse.idx   = 0x00;
    treeElemParse.nMax  = strlen(pArrArguments);

    printf("Input string: %s \n", pArrArguments);
    printf("strlen()= %x \n", treeElemParse.nMax);

    TreeObjParse_V0(&pRootTreeObj, &treeElemParse);

    treeElemControl.nCalls  = 0x00;
    treeElemControl.nMAX    = MAX_AMOUNT_OF_CALLS;
    treeElemControl.exitOnCall = 0x00;
    TreeObjPrintAllTree(pRootTreeObj, &treeElemControl, 0x00);

    treeElemControl.nCalls  = 0x00;
    treeElemControl.nMAX    = MAX_AMOUNT_OF_CALLS;
    treeElemControl.exitOnCall = 0x00;
    TreeObjEvaluateTree(pRootTreeObj, &treeElemControl);
    printf("| %s = %f \n", pArrArguments, pRootTreeObj->value);

    treeElemControl.nCalls  = 0x00;
    treeElemControl.nMAX    = MAX_AMOUNT_OF_CALLS;
    treeElemControl.exitOnCall = 0x00;
    TreeObjReliseAllMemory(pRootTreeObj, &treeElemControl);
}
//===================================================================================================

#endif // _TREE_OBJECT_TEST_H