#include "_sort_function_inc.h"
#ifdef _SORT_QUICK_MY_FUNS_H

#include <stdio.h>
#include <stdint.h>

#define STR_END_MARK    0x00 // Value of end of the string
#define MAX_STRING_LEN  0x10 // Maximum lenght of string characters
#define MAX_LIST_LEN    0x10 // Maximun lenght of list

void PrintListOfNumbers(uint8_t *pNumbers, uint8_t n);
void SortBuble(uint8_t *pNumbers, uint8_t MAX);
void SortQuick_v2(uint8_t *pNumbers, uint8_t MAX);

#endif // _SORT_QUICK_MY_FUNS_H