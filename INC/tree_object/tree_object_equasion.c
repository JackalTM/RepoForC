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
 * @name        TreeObj CreateOperation
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
 * @name        TreeObj CreateValue  
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
 * @name        TreeObj NewNodeInTree  
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

#ifdef TREE_OBJECT_EQUASION_DEBUG_PRINT
    printf("DEBUG: ADDR:= malloc(%x)\n", pNewTreeElem);
#endif

    *pNewTreeElem = newNode;
    return pNewTreeElem;
}
//===================================================================================================

/****************************************************************************************************
 * @name        TreeObj PrintAllTree
 * @brief       Print all equqsions for tree
 * 
 * @param[in]   pTreeElement Pointer to tree object structure  
 * @param[in]   pTreeElemControl Pointer to call control diagnose
 * @param[in]   level Indentetion lever for print
 * 
 * @note        This function called recurency
 * @return      void      
*/
void TreeObjPrintAllTree(treeElement_t* pTreeElement, treeElemControl_t* pTreeElemControl, unsigned int level)
{
    pTreeElemControl->nCalls++;
    if((pTreeElement == NULL) || (pTreeElemControl->nCalls > pTreeElemControl->nMAX))
    {   pTreeElemControl->exitOnCall = pTreeElemControl->nCalls;
        return;}

    unsigned int i;
    for(i=0; i< level; i++)
    {   putchar(' ');}
    printf("| ");

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
 * @name        TreeObj EvaluateTree
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
    if((pTreeElement == NULL) || (pTreeElemControl->nCalls > pTreeElemControl->nMAX))
    {   pTreeElemControl->exitOnCall = pTreeElemControl->nCalls;
        return; }
        
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
 * @name        TreeObj ReliseAllMemory
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
    if((pTreeElement == NULL) || (pTreeElemControl->nCalls > pTreeElemControl->nMAX)) 
    {   pTreeElemControl->exitOnCall = pTreeElemControl->nCalls;
        return; }

    TreeObjReliseAllMemory(pTreeElement->pTreeElemLeft, pTreeElemControl);
    TreeObjReliseAllMemory(pTreeElement->pTreeElemRigh, pTreeElemControl);

#ifdef TREE_OBJECT_EQUASION_DEBUG_PRINT
    printf("DEBUG: ADDR:=  free(%x) val:= %x \n", pTreeElement, pTreeElement->value);
#endif // TREE_OBJECT_EQUASION_DEBUG_PRINT

    free(pTreeElement);
}
//===================================================================================================

/****************************************************************************************************
 * @name        _CharToNumb    
 * @brief       Private function for conversion input char to number from 0 to F.
 * 
 * @param[in]   inChar
 * 
 * @note           
 * @return      char - Converted value of char type    
*/
static char _CharToNumb(char inChar)
{
    if((inChar >= '0') && (inChar <= '9'))
    {   inChar = (inChar - '0');}
    else
    {// When other number return fault
        inChar = WRONG_VALUE;}
        
    return inChar;
}
//===================================================================================================

/****************************************************************************************************
 * @name        _ChequeIfMark    
 * @brief       Private function to check if character is an operation
 * 
 * @param[in]   inChar
 * 
 * @note           
 * @return      char - Operation if char is this type  
*/
static char _ChequeIfMark(char inChar)
{
    switch (inChar)
    {
        case    '+':       break;
        case    '-':       break;
        case    '*':       break;
        case    '/':       break;
    
    default:
        return WRONG_VALUE;
    }
    return inChar;
}
//===================================================================================================

/****************************************************************************************************
 * @name        TreeObj Parse_Alpha    
 * @brief       Version Aplpha
 * 
 * @param[in]   ppTreeElement Pointer to modyfi pointer to tree object
 * @param[in]   pTreeElemParse Input array of chars for calculation
 * 
 * @note           
 * @return      void  
*/
void TreeObjParse_Alpha(treeElemParse_t* pTreeElemParse)
{
    char tCharNumb = (char)(pTreeElemParse->pStr[pTreeElemParse->idx]);
    char tCharMark = tCharNumb;
    pTreeElemParse->idx = pTreeElemParse->idx + 0x01;

    // End of line
    if(pTreeElemParse->idx > pTreeElemParse->nMax)
    {   printf("return \n", tCharNumb); 
       return; }

    // Cheque if char is number
    tCharNumb = _CharToNumb(tCharNumb);
    if(tCharNumb != WRONG_VALUE)
    {// Input char is Number from 0 to F
        printf("| numb %x | \n", tCharNumb);}

    // Cheque if char is operator
    tCharMark = _ChequeIfMark(tCharMark);
    if(tCharMark != WRONG_VALUE)
    {// Input character is operation, then create new node for calculation.
        printf("| mark %c | \n", tCharMark);}   

    TreeObjParse_Alpha(pTreeElemParse);
}
//===================================================================================================

/****************************************************************************************************
 * @name        TreeObj Parse_Beta    
 * @brief       Version Beta
 * 
 * @param[in]   ppTreeElement Pointer to modyfi pointer to tree object
 * @param[in]   pTreeElemParse Input array of chars for calculation
 * 
 * @note           
 * @return      void
*/
void TreeObjParse_Beta(treeElement_t** ppTreeElement, treeElemParse_t*  pTreeElemParse)
{
    char tCharNumb = (char)(pTreeElemParse->pStr[pTreeElemParse->idx]);
    char tCharMark = tCharNumb;
    pTreeElemParse->idx = pTreeElemParse->idx + 0x01;

    // End of line
    if(pTreeElemParse->idx > pTreeElemParse->nMax)
    {   return;}

    // Cheque if char is number
    tCharNumb = _CharToNumb(tCharNumb);
    if(tCharNumb != WRONG_VALUE)
    {// Input char is Number from 0 to F
        *ppTreeElement  = TreeObjNewNodeInTree(TreeObjCreateValue(tCharNumb));
        return; }

    // Cheque if char is operator
    tCharMark = _ChequeIfMark(tCharMark);
    if(tCharMark != WRONG_VALUE)
    {// Input character is operation, then create new node for calculation.
        treeElement_t* pNewTreeElement = TreeObjNewNodeInTree(TreeObjCreateOperation(tCharMark));

        TreeObjParse_Beta(&(pNewTreeElement->pTreeElemLeft), pTreeElemParse);
        TreeObjParse_Beta(&(pNewTreeElement->pTreeElemRigh), pTreeElemParse);

        *ppTreeElement = pNewTreeElement;
        return; }
}
//===================================================================================================

/****************************************************************************************************
 * @name        TreeObjParse_V0    
 * @brief       Version V0.0
 * 
 * @param[in]   ppTreeElement Pointer to modyfi pointer to tree object
 * @param[in]   pTreeElemParse Input array of chars for calculation
 * 
 * @note        Bug fixed with only one branch
 * @return      void
*/
void TreeObjParse_V0(treeElement_t** ppTreeElement, treeElemParse_t* pTreeElemParse)
{
    char tCharNumb = (char)(pTreeElemParse->pStr[pTreeElemParse->idx]);
    char tCharMark = tCharNumb;
    (pTreeElemParse->idx)++;

    // End of line
    if(pTreeElemParse->idx > pTreeElemParse->nMax)
    {   return; }

    // Cheque if char is number
    tCharNumb = _CharToNumb(tCharNumb);
    if(tCharNumb != WRONG_VALUE)
    {// Input char is Number from 0 to F
        *ppTreeElement  = TreeObjNewNodeInTree(TreeObjCreateValue(tCharNumb));
        return; }

    // Cheque if char is operator
    tCharMark = _ChequeIfMark(tCharMark);
    if(tCharMark != WRONG_VALUE)
    {// Input character is operation, then create new node for calculation.
        treeElement_t* pNewTreeElement = TreeObjNewNodeInTree(TreeObjCreateOperation(tCharMark));

        TreeObjParse_V0(&(pNewTreeElement->pTreeElemLeft), pTreeElemParse);
        TreeObjParse_V0(&(pNewTreeElement->pTreeElemRigh), pTreeElemParse);

        *ppTreeElement = pNewTreeElement;
        return; }
}
//===================================================================================================

#endif // _TREE_OBJECT_EQUASION_H