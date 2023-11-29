#include "tree_object_equasion.h"
#ifdef _TREE_OBJECT_EQUASION_H

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
 * @name        CreateOperation
 * @brief       Create operation for tree 
 * 
 * @param[in]   op - Type of operation as char 
 * 
 * @note        To existing node operation is added.
 *          
 * @return      treeElement_t object     
*/
treeElement_t TreeObjCreateOperation(char op)
{
    treeElement_t newOperationElement;

    newOperationElement.operation = op;
    newOperationElement.value = 0;
    newOperationElement.calculationState = TREE_OBJ_OPR_STATE_FALSE;

    newOperationElement.pTreeElemLeft = NULL;
    newOperationElement.pTreeElemRigh = NULL;

    return newOperationElement;
}
//===================================================================================================

/****************************************************************************************************
 * @name        CreateValue  
 * @brief       Add value for the oparation
 * 
 * @param[in]   value - Value for operation   
 * 
 * @note        To existing node value is added
 *         
 * @return      treeElement_t object structure
*/
treeElement_t TreeObjCreateValue(double value)
{
    treeElement_t newValueElement;

    newValueElement.operation = TREE_OBJ_OPR_NONE;
    newValueElement.value = value;
    newValueElement.calculationState = TREE_OBJ_OPR_STATE_TRUE;

    newValueElement.pTreeElemLeft = NULL;
    newValueElement.pTreeElemRigh = NULL;

    return newValueElement;
}
//===================================================================================================

/****************************************************************************************************
 * @name        NewNodeInTree  
 * @brief       Creation new note of a tree.
 *              After alocating memory data in asigned
 * 
 * @param[in]   newNode - New node for tree element object   
 * @param[in]   
 * 
 * @note           
 * @return      Ponter of a type (treeElement_t*)
*/
treeElement_t* TreeObjNewNodeInTree(treeElement_t newNode)
{
    treeElement_t* pNewTreeElem;
    pNewTreeElem = (treeElement_t*)malloc(sizeof(treeElement_t));

    *pNewTreeElem = newNode;
    return pNewTreeElem;
}
//===================================================================================================

/****************************************************************************************************
 * @name        PrintAllTree
 * @brief       Print all equqsions for tree
 * 
 * @param[in]   pTreeElement - Pointer to tree object structure  
 * @param[in]   level - Level of the tree structure
 * 
 * @note           
 * @return      void      
*/
void TreeObjPrintAllTree(treeElement_t* pTreeElement, treeElemControl_t* pTreeElemControl, unsigned int level)
{
    pTreeElemControl->nCalls++;
    if((pTreeElemControl->nCalls > MAX_AMOUNT_OF_CALLS) || (pTreeElement == NULL)) 
    {
        pTreeElemControl->errorOnCall = pTreeElemControl->nCalls;
        return;
    }

    unsigned int i;
    for(i=0; i< level; i++)
    {
        putchar(' ');
    }
    printf("|- ");

    if(pTreeElement->operation != TREE_OBJ_OPR_NONE)
    {
        printf("%c\t", pTreeElement->operation);
    }

    if(pTreeElement->calculationState == TREE_OBJ_OPR_STATE_TRUE)
    {
        printf("%.2f\n", pTreeElement->value);
    }
    else
    {
        printf("?\n");
    }

    TreeObjPrintAllTree(pTreeElement->pTreeElemLeft, pTreeElemControl, level + 1);
    TreeObjPrintAllTree(pTreeElement->pTreeElemRigh, pTreeElemControl, level + 1);
}
//===================================================================================================

/****************************************************************************************************
 * @name        EvaluateTree
 * @brief       Evaluate tree object
 * 
 * @param[in]   pTreeElement - Pointer to tree object structure  
 * 
 * @note           
 * @return     void  
*/
void TreeObjEvaluateTree(treeElement_t* pTreeElement, treeElemControl_t* pTreeElemControl)
{
    pTreeElemControl->nCalls++;
    if((pTreeElemControl->nCalls > MAX_AMOUNT_OF_CALLS) || (pTreeElement == NULL))
    {
        pTreeElemControl->errorOnCall = pTreeElemControl->nCalls;
        return;
    }
        

    TreeObjEvaluateTree(pTreeElement->pTreeElemLeft, pTreeElemControl);
    TreeObjEvaluateTree(pTreeElement->pTreeElemRigh, pTreeElemControl);

    if(pTreeElement->operation != TREE_OBJ_OPR_NONE)
    {
        treeElement_t* pTemp;

        pTemp = pTreeElement->pTreeElemLeft;
        double tDoubleA = pTemp->value;

        pTemp = pTreeElement->pTreeElemRigh;
        double tDoubleB = pTemp->value;

        switch (pTreeElement->operation)
        {
        case TREE_OBJ_OPR_ADD:
            tDoubleA = tDoubleA + tDoubleB;
            break;

        case TREE_OBJ_OPR_SUB:
            tDoubleA = tDoubleA - tDoubleB;
            break;

        case TREE_OBJ_OPR_MUL:
            tDoubleA = tDoubleA * tDoubleB;
            break;

        case TREE_OBJ_OPR_DIV:
            tDoubleA = tDoubleA / tDoubleB;
            break;
        
        default:
            break;
        }

        pTreeElement->value = tDoubleA;
        pTreeElement->calculationState = TREE_OBJ_OPR_STATE_TRUE;
    }

    return;
}
//===================================================================================================

/****************************************************************************************************
 * @name        TreeObjReliseAllMemory
 * @brief       Relise memory for a alocated tree object.
 *              Memory need to be free acording to structure
 * 
 * @param[in]   pTreeElement Pointer to root tree object
 * @param[in]   
 * 
 * @note           
 * @return      void 
*/
void TreeObjReliseAllMemory(treeElement_t* pTreeElement, treeElemControl_t* pTreeElemControl)
{
    pTreeElemControl->nCalls++;
    if(pTreeElement == NULL) return;

    TreeObjReliseAllMemory(pTreeElement->pTreeElemLeft, pTreeElemControl);
    TreeObjReliseAllMemory(pTreeElement->pTreeElemRigh, pTreeElemControl);

#ifdef TREE_OBJECT_EQUASION_DEBUG_PRINT
    printf("DEBUG: ADDR:=  free(%x) \n", pTreeElement);
#endif // TREE_OBJECT_EQUASION_DEBUG_PRINT

    free(pTreeElement);
}
//===================================================================================================


#endif // _TREE_OBJECT_EQUASION_H