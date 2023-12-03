#include "functions_declaration.h"
#ifdef _FUNCTION_DECLARATIONS_H

/*************************************************************************************************
 * @name    
 * @brief
 * @param   
 * @note
 * @return
*/
uint32_t LogicalAND(uint32_t inA, uint32_t inB)
{
    return (inA & inB);
}
//=================================================================================================

/*************************************************************************************************
 * @name    
 * @brief
 * @param   
 * @note
 * @return
*/
uint32_t LogicalOR(uint32_t inA, uint32_t inB)
{
    return (inA | inB);
}
//=================================================================================================

/*************************************************************************************************
 * @name    
 * @brief
 * @param   
 * @note
 * @return
*/
uint32_t LogicalXOR(uint32_t inA, uint32_t inB)
{
    inA = ~inA;

    return (inA | inB);
}
//=================================================================================================

/*************************************************************************************************
 * @name    
 * @brief
 * @param   
 * @note
 * @return
*/
uint32_t LogicalNOT(uint32_t inA)
{
    return (~inA);
}
//=================================================================================================

/*************************************************************************************************
 * @name    
 * @brief
 * @param   
 * @note
 * @return
*/
uint8_t CompareBYTE(uint8_t inA, uint8_t inB)
{
    if(inA == inB)          {return COMPARE_RESOULT_SAME;}
    else if(inA > inB)      {return COMPARE_RESOULT_MORE;}
    else if(inA < inB)      {return COMPARE_RESOULT_LESS;}
}
//=================================================================================================

/*************************************************************************************************
 * @name    
 * @brief
 * @param   
 * @note
 * @return
*/
uint8_t CompareDWORD(uint32_t inA, uint32_t inB)
{
    if(inA == inB)          {return COMPARE_RESOULT_SAME;}
    else if(inA > inB)      {return COMPARE_RESOULT_MORE;}
    else if(inA < inB)      {return COMPARE_RESOULT_LESS;}
}
//=================================================================================================

#endif // _FUNCTION_DECLARATIONS_H