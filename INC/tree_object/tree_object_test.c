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

    treeElemControl.nCalls = 0x00;
    treeElemControl.errorOnCall = 0x00;
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

    treeElemControl.nCalls = 0x00;
    treeElemControl.errorOnCall = 0x00;
    TreeObjPrintAllTree(&obj2, &treeElemControl, 0x00);

    treeElemControl.nCalls = 0x00;
    treeElemControl.errorOnCall = 0x00;
    TreeObjEvaluateTree(&obj2, &treeElemControl);

    printf("\n\n After calculation \n");

    treeElemControl.nCalls = 0x00;
    treeElemControl.errorOnCall = 0x00;
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
void CALL_treeTest03(void)
{
    // 1 + 2 * 3
    treeElemControl_t treeElemControl;
    treeElement_t* pRootTreeObj;

    pRootTreeObj = TreeObjNewNodeInTree(TreeObjCreateOperation(TREE_OBJ_OPR_ADD));
    pRootTreeObj->pTreeElemLeft = TreeObjNewNodeInTree(TreeObjCreateValue(1));
    pRootTreeObj->pTreeElemRigh = TreeObjNewNodeInTree(TreeObjCreateOperation(TREE_OBJ_OPR_MUL));

    pRootTreeObj->pTreeElemRigh->pTreeElemLeft = TreeObjNewNodeInTree(TreeObjCreateValue(2));
    pRootTreeObj->pTreeElemRigh->pTreeElemRigh = TreeObjNewNodeInTree(TreeObjCreateValue(3));

    treeElemControl.nCalls = 0x00;
    treeElemControl.errorOnCall = 0x00;
    TreeObjPrintAllTree(pRootTreeObj, &treeElemControl, 0x00);

    treeElemControl.nCalls = 0x00;
    treeElemControl.errorOnCall = 0x00;
    TreeObjEvaluateTree(pRootTreeObj, &treeElemControl);

    printf("\n\nAfter calculation method 3\n");

    treeElemControl.nCalls = 0x00;
    treeElemControl.errorOnCall = 0x00;
    TreeObjPrintAllTree(pRootTreeObj, &treeElemControl, 0x00);

    printf("\n -- Amount of self calls:= %2x \n", treeElemControl.nCalls);

    TreeObjReliseAllMemory(pRootTreeObj, &treeElemControl);
}
//===================================================================================================

#endif // _TREE_OBJECT_TEST_H