#include <stdio.h>      /* printf, scanf, NULL */
#include <stdint.h>
#include <stdlib.h>     /* malloc, free, rand */
#include <conio.h>

#define EXC_QUEST_ARRAY_MAX (uint8_t)(0x20)

/***********************************************************************************************
 * 
*/
typedef struct full_byte
{
    uint8_t data1 : 4;
    uint8_t data2 : 4;
}byteDataSliceStruct_t;

typedef union 
{
    uint8_t                 data;
    byteDataSliceStruct_t   dataSlise;
}byteDataSliceUnion_t;
//=============================================================================================

/***********************************************************************************************
 * 
*/
#define DATA_LEN 8
typedef struct MemoryMember_t
{
    struct MemoryMember_t *pPrev;
    struct MemoryMember_t *pNext;
    uint8_t mydata[DATA_LEN];
}MemoryMember_t;
typedef struct
{
    struct MemoryMember_t *pTail;
    struct MemoryMember_t *pHead; 
    uint8_t n;
    uint8_t init;
}MallocControlData_t;
//=============================================================================================

/***********************************************************************************************
 * 
*/
uint8_t RemoveDuplicatesInArray(char* pArraySRC, uint8_t nSCRmax);

/***********************************************************************************************
 * 41. Write a program to get the higher and lower nibble of a byte without using shift operator?
*/

uint8_t DataSliceWithUnion(void);
//==============================================================================================

/***********************************************************************************************
 * 43. Write a C program to check if it is a palindrome number or not using a recursive method.
*/
uint8_t PalindromeNumber(uint32_t Num);
//==============================================================================================

/***********************************************************************************************
 * 44. C program to check the given number format is in binary or not.
*/
uint32_t CheckIfNumberIsBinary(uint32_t Num);
//==============================================================================================

/***********************************************************************************************
 * 45. C Program to find a sum of digits of a number using recursion.
*/
uint8_t SumByRecursion(uint32_t Num);
//==============================================================================================

/***********************************************************************************************
 * 52. When is the "void" keyword used in a function
*/
void Question52_MyMemCopy(void* pDst, const void* pSrc, int numBytes);
//==============================================================================================

/***********************************************************************************************
 * 54. Add Two Numbers Without Using the Addition Operator
*/
int Question54_addTwoNUmbers(int num1, int num2);
//==============================================================================================

/***********************************************************************************************
 * 55. Subtract Two Number Without Using Subtraction Operator
*/
int Question55_subTwoNUmbers(int num1, int num2);
//==============================================================================================

/***********************************************************************************************
 * 56. Multiply an Integer Number by 2 Without Using Multiplication Operator
*/
int Question56_multiplyNumber(int num);
//==============================================================================================

/***********************************************************************************************
 * 57. Check whether the number is EVEN or ODD, without using any arithmetic or relational operators
*/
int Question56_number_EvenOrOdd(int num);
//==============================================================================================

/***********************************************************************************************
 * 58. Reverse the Linked List. Input: 1->2->3->4->5->NULL Output: 5->4->3->2->1->NULL
*/

void Question56_reverseObjectsList(MallocControlData_t* pMallocControlData);
//==============================================================================================

/***********************************************************************************************
 * 59. Check for Balanced Parentheses using Stack
*/
int Question59_check(char exp[] );
//==============================================================================================

/***********************************************************************************************
 * 60. Program to find n’th Fibonacci number
*/
int Question60_fib(int n);
int Question60_fibcall(int n);
//==============================================================================================

/***********************************************************************************************
 * 61. Write a program to find the node at which the intersection of two singly linked lists begins.
*/ 
int Question61_getIntersectionNode(MallocControlData_t pMallocControlData1, MallocControlData_t pMallocControlData2);
//==============================================================================================

/***********************************************************************************************
 * 62. Merge Two sorted Linked List
*/
void Question62_merge_sorted(MallocControlData_t pMallocControlData1, MallocControlData_t pMallocControlData2);
//==============================================================================================