#include <stdio.h>
#include <stdint.h>

#define STR_END_MARK    0x00 // Value of end of the string
#define MAX_STRING_LEN  0x10 // Maximum lenght of string characters
#define MAX_LIST_LEN    0x10 // Maximun lenght of list

void PrintList(uint8_t *pNumbers);
void MoveStr_Dest_Source(char *pStrDest, char *pStrSource);
uint8_t CompareString(char *str11, char *str22);
void SortQuickString(char **ppStrings, uint8_t iListMaxLen);
void SortQuickInt(uint8_t *pNumbers, uint8_t maxLen);

void CallTestSort(void);