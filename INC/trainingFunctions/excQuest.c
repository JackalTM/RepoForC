#include "excQuest.h"

/*******************************************************************************
 * @name    static AmountOfElementsInArray
 * @brief   ...
 * @param   ...
 * @param   ...
 * @note    ...
 * @return  uint8_t
*/
static void _PrintArray(char* pArray, uint8_t n)
{
  uint8_t i;
  printf("LIST: \n");
  
  for(i=0; i<n; i++)
  {
    printf("| %x = %x | ", i, pArray[i]);
  }
  printf("\n");
}
/*******************************************************************************
 * @name    RemoveDuplicatesInArray
 * @brief   Check list for duplicates elements
 * @param   pArraySRC - Pointer to source array
 * @param   nSCRmax   - Source array element amount
 * @note    ...
 * @return  Lenght of the new list
*/
uint8_t RemoveDuplicatesInArray(char* pArraySRC, uint8_t nSCRmax)
{
  char arrList[EXC_QUEST_ARRAY_MAX];
  char arrHead = 0x00;

  uint8_t i, j, idx;

  if(nSCRmax >= EXC_QUEST_ARRAY_MAX) return 0xFF;

  for(i=0; i<nSCRmax; i++)
  {// Loop throught all elements in source list

    for(j=0; j<arrHead; j++)
    {
      if(pArraySRC[i] == arrList[j]) 
      {// Element is not unique.
        goto NOT_UNIQ;}
    }
    
    // In new list element is not fount.
    // Element is unique.
    arrList[arrHead] = pArraySRC[i];
    arrHead++;
  
    NOT_UNIQ:;
  }

  for(j=0; j<arrHead; j++)
  { pArraySRC[j] = arrList[j];}

  return arrHead;   
}

/***********************************************************************************************
 * 41. Write a program to get the higher and lower nibble of a byte without using shift operator?
*/
uint8_t DataSliceWithUnion(void)
{
  byteDataSliceUnion_t  tData;

  tData.data = 0xAB;

  printf("BYTE = %x \n", tData.data);
  printf("LOW BYTE = %x HIGH BYTE = %x \n", tData.dataSlise.data1, tData.dataSlise.data2);

  return 0;
}
//=============================================================================================

/***********************************************************************************************
 * 43. Write a C program to check if it is a palindrome number or not using a recursive method.
*/
static uint32_t _PalindromeNumberReverse(uint32_t* pSum, uint32_t Num)
{
  uint32_t rem;
  if(Num != 0)
  {
    rem = Num % 0x10;
    *pSum = (*pSum) * 0x10 + rem;
    _PalindromeNumberReverse(pSum, (Num / 0x10));
    return *pSum;
  }
  else  
  { return *pSum;}
}
uint8_t PalindromeNumber(uint32_t Num)
{
  uint32_t tSum = (uint32_t)0x00;

  printf("========================================== \n");
  printf("Is the given numbe a palindrome??? %X \n", Num);

  if(Num == _PalindromeNumberReverse(&tSum, Num))
  { printf("TRUE \n");}
  else
  { printf("FALSE \n");}

  printf("========================================== \n");

  return 0x00;
}
//==============================================================================================

/***********************************************************************************************
 * 44. C program to check the given number format is in binary or not.
*/
uint32_t CheckIfNumberIsBinary(uint32_t Num)
{
	uint32_t res;

  printf("========================================== \n");
	printf("Does number %x is binary?? \n", Num);

  while((Num > 0x00) && (Num < 0xFFFFFFF0))
  {
    res = Num % 0x10;
    if((res != 0x0) && (res != 0x1))
    {
      printf("FALSE \n");
      break;
    }
    else
    { Num = Num / 0x10;}
    
    if(Num == 0x00)
    { printf("TRUE \n");}
  }

  printf("========================================== \n");

  return 0x00;
}
//==============================================================================================

/***********************************************************************************************
 * 45. C Program to find a sum of digits of a number using recursion.
*/
static int32_t _SumByRecursionSum(uint32_t* pSum, uint8_t* pCallsAmount, uint32_t num)
{
  uint32_t rem;

  if(*(pCallsAmount) > 0x8)  { return -1;}
  else                      { *(pCallsAmount) = *(pCallsAmount) + 1;}

  *pSum = *pSum + (num % 0x10);
  rem = num / 0x10;

  if(rem > 0x00)  { _SumByRecursionSum(pSum, pCallsAmount, rem);}
  else            { return *pSum;}
}
uint8_t SumByRecursion(uint32_t Num)
{
  uint32_t  tSum = 0x00;
  uint8_t   tCallsAmount = 0x00;

  printf("========================================== \n");
	printf("Sum of digits from a number %x \n", Num);

  Num = _SumByRecursionSum((uint32_t*)&tSum, (uint8_t*)&tCallsAmount, Num);

  printf("Sum of digits = %x \n", Num);
  printf("Recursion number = %x \n", tCallsAmount);

  printf("========================================== \n");
}
//==============================================================================================

/***********************************************************************************************
 * 52. When is the "void" keyword used in a function
*/
void Question52_MyMemCopy(void* pDst, const void* pSrc, int numBytes) 
{ 
  int i;
	char* pDst_c;
	char* pSrc_c;

	pDst_c       = (char*)(pDst); 
	pSrc_c = (char*)(pSrc);

	for (i = 0; i < numBytes; ++i) 
  {
    *(pDst_c + i) = *(pSrc_c + i);
  }
}
//==============================================================================================

/***********************************************************************************************
 * 54. Add Two Numbers Without Using the Addition Operator
*/
int Question54_addTwoNUmbers(int num1, int num2)
{
  int x, y;
  printf("========================================== \n");
  printf("Two numbers add  %d + %d \n", num1, num2);
  x = num1;
  y = num2;

  // method 1
  printf("%d\n", x - (-y));

  // method 2
  printf("%d\n", -(-x -y));

  // method 3
  printf("%d\n", abs(-x -y));

  // method 4
  printf("%d", x - (~y) - 1);
  printf("========================================== \n");

  return 0;
}
//==============================================================================================

/***********************************************************************************************
 * 55. Subtract Two Number Without Using Subtraction Operator
*/
int Question55_subTwoNUmbers(int num1, int num2)
{
  printf("========================================== \n");
  printf("Two numbers sub  %d + %d \n", num1, num2);

  printf("%d", num1 + (~num1) + 1);
  printf("========================================== \n");

  return 0;
}
//==============================================================================================

/***********************************************************************************************
 * 56. Multiply an Integer Number by 2 Without Using Multiplication Operator
*/
int Question56_multiplyNumber(int num)
{
  int x;
  printf("========================================== \n");
  printf("Number %d to multiply by 2 \n");

  x = num << 1;
  printf("%d", x<<1);
  printf("========================================== \n");
  return 0;
}
//==============================================================================================

/***********************************************************************************************
 * 57. Check whether the number is EVEN or ODD, without using any arithmetic or relational operators
*/
int Question57_number_EvenOrOdd(int num)
{
  int x;
  x = num;
  printf("========================================== \n");
  printf("NUmber to check %d \n", num);

  (x&1)?printf("ODD \n"):printf("EVEN \n");

  printf("========================================== \n");
  return 0;
}
//==============================================================================================

/***********************************************************************************************
 * 58. Reverse the Linked List. Input: 1->2->3->4->5->NULL Output: 5->4->3->2->1->NULL
*/
/*******************************************************************************
 * @name    RemoveDuplicatesInArray
 * @brief   Reverse Head and tail direction in dynamic obj alocation
 * @param   pMallocControlData  Pointer to dynamic object structure
 * @note    See MallocControlData_t structure
 * @return  uint8_t
*/
void ReverseDynamicListObj(MallocControlData_t* pMallocControlData)
{ 
  if(pMallocControlData->init != 0xFF)  return;
  if(pMallocControlData->n == 0x00)     return;

  MemoryMember_t* pCurrent  = pMallocControlData->pHead;
  MemoryMember_t* pPrev     = NULL; 
  MemoryMember_t* pNext     = NULL;

// Input: 1-> 2-> 3-> 4-> 5-> NULL Output: 5->4->3->2->1->NULL

// (pPrev)=[ curr ]=(pNext) ; (pPrev)=[ curr ]=(pNext) ; (pPrev)=[ curr ]=(pNext) ; (pPrev)=[ curr ]=(pNext) ;
// (NULL )=[ obj1 ]=(&obj2) ; (obj1 )=[ obj2 ]=(&obj3) ; (obj2 )=[ obj3 ]=(&obj4) ; (obj3 )=[ obj4 ]=(NULL )

  uint8_t i;
  for(i=0; i<(pMallocControlData->n); i++)
  {
    pNext = pCurrent->pNext;
    pPrev = pCurrent->pPrev;

    pCurrent->pNext = pPrev;
    pCurrent->pPrev = pNext;

    if(pNext == NULL) break;
    else   pCurrent = pNext;
  }
}
//==============================================================================================

/***********************************************************************************************
 * 59. Check for Balanced Parentheses using Stack
*/
int Question59_check(char exp[] )
{
  /*
  int i;
  char temp;
  for(i=0; i<strlen(exp); i++)
  {
    if(exp[i]=='(' || exp[i]=='{' || exp[i]=='[') { push(exp[i]);}

    if(exp[i]==')' || exp[i]=='}' || exp[i]==']')
    {
      if(top == -1)    //stack empty
      {
        printf("Right parentheses are more than left parentheses\n");
        return 0;
      }
      else
      {
        temp=pop();
        if(!match(temp, exp[i]))
        {
          printf("Mismatched parentheses are : ");
          printf("%c and %c\n",temp,exp[i]);
          return 0;
        }
      }
    }
  }

  if(top==-1) //stack empty
  {
    printf("Balanced Parentheses\n");
    return 1;
  }
  else
  {
    printf("Left parentheses more than right parentheses\n");
    return 0;
  }
  */
}
//==============================================================================================

/***********************************************************************************************
 * 60. Program to find n’th Fibonacci number
*/
int Question60_fib(int n)
{
  if (n <= 1) 
  { return n;}

  return Question60_fib(n - 1) + Question60_fib(n - 2);
}
 
int Question60_fibcall(int n)
{
  printf("nth Fibonacci number is %d", Question60_fib(n));

  return 0;
}
//==============================================================================================

/***********************************************************************************************
 * 61. Write a program to find the node at which the intersection of two singly linked lists begins.
*/ 
int Question61_getIntersectionNode(MallocControlData_t pMallocControlData1, MallocControlData_t pMallocControlData2) 
{ 
  uint8_t i,j;
  MemoryMember_t* pOBJ11 = pMallocControlData1.pHead;
  MemoryMember_t* pOBJ22 = pMallocControlData2.pHead;
  MemoryMember_t* pCURR;

  for(i=0; pMallocControlData1.n; i++)
  {
    pCURR = pOBJ11->pNext;
  }
  for(j=0; pMallocControlData2.n; j++)
  {

  }
}
//==============================================================================================

/***********************************************************************************************
 * 62. Merge Two sorted Linked List
*/
void Question62_merge_sorted(MallocControlData_t pMallocControlData1, MallocControlData_t pMallocControlData2)
{  
  // if both lists are empty then merged list is also empty
  // if one of the lists is empty then other is the merged list
  if((pMallocControlData1.pHead == NULL) && (pMallocControlData1.pTail == NULL))
  {
    ;
  }
  if((pMallocControlData2.pHead == NULL) && (pMallocControlData2.pTail == NULL))
  {
    ;
  }

  

  /*
  if (head1 == void*0) 
  {
    return head2;
  } 
  else if (head2 == nullptr) 
  {
    return head1;
  }


  Node_t mergedHead = nullptr;
  if (head1->data <= head2->data) 
  {
    mergedHead = head1;
    head1 = head1->next;
  } 
  else 
  {
    mergedHead = head2;
    head2 = head2->next;
  }

  NodePtr mergedTail = mergedHead;
  
  while (head1 != nullptr && head2 != nullptr) 
  {
    NodePtr temp = nullptr;
    if (head1->data <= head2->data) 
    {
      temp = head1;
      head1 = head1->next;
    } 
    else 
    {
      temp = head2;
      head2 = head2->next;
    }

    mergedTail->next = temp;
    mergedTail = temp;
  }

  if (head1 != nullptr) 
  {
    mergedTail->next = head1;
  } 
  else if (head2 != nullptr) 
  {
    mergedTail->next = head2;
  }

  return mergedHead;
  */
}
//==============================================================================================