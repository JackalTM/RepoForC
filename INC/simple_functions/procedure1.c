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

void CALL_ProcedureTest(void)
{
  char s[64];
  puts(itoa_simple(s, 0xFF));

  puts(itoa_simple(s, 0xF0));

}


#endif // PROCEDURE1_H