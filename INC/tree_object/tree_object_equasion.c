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
 * @param[in]   op Type of operation as char 
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
 * @param[in]   value Value for operation   
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
 * @param[in]   newNode New node for tree element object   
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
 * @param[in]   pTreeElement Pointer to tree object structure  
 * @param[in]   pTreeElemControl Pointer to call control diagnose
 * @param[in]   level Indentetion lever for print
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
    {   putchar(' ');}
    printf("|- ");

    if(pTreeElement->operation != TREE_OBJ_OPR_NONE)
    {   printf("%c\t", pTreeElement->operation);}

    if(pTreeElement->calculationState == TREE_OBJ_OPR_STATE_TRUE)
    {   printf("%.2f\n", pTreeElement->value);}
    else
    {   printf("?\n");}

    TreeObjPrintAllTree(pTreeElement->pTreeElemLeft, pTreeElemControl, level + 1);
    TreeObjPrintAllTree(pTreeElement->pTreeElemRigh, pTreeElemControl, level + 1);
}
//===================================================================================================

/****************************************************************************************************
 * @name        EvaluateTree
 * @brief       Evaluate tree object
 * 
 * @param[in]   pTreeElement Pointer to tree object structure  
 * @param[in]   pTreeElemControl Pointer to call control diagnose
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
            tDoubleA = (double)(0.0);
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
 * @param[in]   pTreeElemControl Pointer to call control diagnose
 * 
 * @note           
 * @return      void 
*/
void TreeObjReliseAllMemory(treeElement_t* pTreeElement, treeElemControl_t* pTreeElemControl)
{
    pTreeElemControl->nCalls++;
    if(pTreeElement == NULL) 
    {   return;}

    TreeObjReliseAllMemory(pTreeElement->pTreeElemLeft, pTreeElemControl);
    TreeObjReliseAllMemory(pTreeElement->pTreeElemRigh, pTreeElemControl);

#ifdef TREE_OBJECT_EQUASION_DEBUG_PRINT
    printf("DEBUG: ADDR:=  free(%x) \n", pTreeElement);
#endif // TREE_OBJECT_EQUASION_DEBUG_PRINT

    free(pTreeElement);
}
//===================================================================================================

/****************************************************************************************************
 * @name        _ConvertCharacter    
 * @brief       Private function for conversion input char to number from 0 to F.
 * 
 * @param[in]   inChar
 * 
 * @note           
 * @return      char - Converted value of char type    
*/
static char _ChequeIfNumber(char inChar)
{
    char retVal;
    if((inChar >= '0') && (inChar <= '9'))
    {
        retVal = (inChar - '0');
    }
    else if((inChar >= 'A') && (inChar <= 'F'))
    {
        retVal = (inChar - 0x37);
    }
    else if((inChar >= 'a') && (inChar <= 'f'))
    {
        retVal = (inChar - 0x57);
    }
    else
    {// When other number return fault
        retVal = 0xFF;
    }

    return retVal;
}
//===================================================================================================

/****************************************************************************************************
 * @name        _ChequeIfOperation    
 * @brief       Private function to check if character is an operation
 * 
 * @param[in]   inChar
 * 
 * @note           
 * @return      char - Operation if char is this type  
*/
static char _ChequeIfOperation(char inChar)
{
    switch (inChar)
    {
    case    '+':       break;
    case    '-':       break;
    case    '*':       break;
    case    '/':       break;
    
    default:
        return 0xFF;
    }

    return inChar;
}
//===================================================================================================
/****************************************************************************************************
 * @name        TreeObjParse    
 * @brief       
 * 
 * @param[in]   ppTreeElement Pointer to modyfi pointer to tree object
 * @param[in]   pInputChar Input array of chars for calculation
 * @param[in]   pIdx Index for input array
 * 
 * @note           
 * @return      
*/
#define _TREE_OBJ_PARSE_DEBUG_PRINT
#define _TREE_OBJ_PARSE_NCALLS_MAX 0x10
static char treeObjParse_cCalls = 0x00;
void TreeObjParse(treeElement_t** ppTreeElement, char pInputChar[], char* pIdx)
{
    treeObjParse_cCalls = treeObjParse_cCalls + 0x01;
    if(treeObjParse_cCalls > _TREE_OBJ_PARSE_NCALLS_MAX) return;

    char tCharNumber = pInputChar[*pIdx];
    char tCharOperator = tCharNumber;
    (*pIdx) = (*pIdx) + 0x01;

    // End of line
    if(tCharNumber == 0x00) return;

    // Cheque if char is number
    tCharNumber = _ChequeIfNumber(tCharNumber);
    if(tCharNumber != 0xFF)
    {// Input char is Number from 0 to F
        *ppTreeElement  = TreeObjNewNodeInTree(TreeObjCreateValue(tCharNumber));
        return;
    }

    // Cheque if char is operator
    tCharOperator = _ChequeIfOperation(tCharOperator);
    if(tCharOperator != 0xFF)
    {// Input character is operation, then create new node for calculation.
        treeElement_t* pNewTreeElement = TreeObjNewNodeInTree(TreeObjCreateOperation(tCharOperator));

        TreeObjParse(&(pNewTreeElement->pTreeElemLeft), pInputChar, pIdx);
        TreeObjParse(&(pNewTreeElement->pTreeElemRigh), pInputChar, pIdx);

        *ppTreeElement = pNewTreeElement;
    }

    return;
}
//===================================================================================================

#endif // _TREE_OBJECT_EQUASION_H