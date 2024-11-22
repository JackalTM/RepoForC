#include "procedure1.h"
#ifdef _PROCEDURE1_H


static char* itoa_simple_helper(char *dest, int i) 
{
  if (i <= -10) 
  {
    dest = itoa_simple_helper(dest, i/10);
  }
  
  *dest++ = '0' - i%10;
  return dest;
}

char *itoa_simple(char *dest, int i) 
{
  char *s = dest;
  if (i < 0) 
  {
    *s++ = '-';
  } 
  else 
  {
    i = -i;
  }
  *itoa_simple_helper(s, i) = '\0';
  return dest;
}

#define IDX_MAX_NCALLS 0
#define IDX_CALLS_AMOU 1
static char* _ConvertToStr(char *pStr, int i, uint8_t arrCalls[]) 
{
  arrCalls[IDX_CALLS_AMOU] = arrCalls[IDX_CALLS_AMOU] + 0x01;
  if(arrCalls[IDX_CALLS_AMOU] > arrCalls[IDX_MAX_NCALLS])
  { return;}

  if (i <= -10) 
  {
    pStr = itoa_simple_helper(pStr, i/10);
  }
  
  *pStr++ = '0' - i%10;
  return pStr;
}
void NumberToString(char* pStr, uint8_t strLen, uint8_t number)
{
  uint8_t arrCalls[2];

  arrCalls[IDX_MAX_NCALLS] = strLen;
  arrCalls[IDX_CALLS_AMOU] = 0x00;
  _ConvertToStr(pStr, number, arrCalls);


}

void CALL_ProcedureTest(void)
{
  char s[64];
  puts(itoa_simple(s, 0xFF));

  puts(itoa_simple(s, 0xF0));

}


#endif // PROCEDURE1_H