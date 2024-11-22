#include "_function_pointers.h"
#ifdef _FUNCTION_POINTERS1_H

#include <stdio.h>      /* printf, scanf, NULL */
#include <stdint.h>
#include <stdlib.h>     /* malloc, free, rand */
#include "functions_declaration.h"
#include "structures_declarations.h"

typedef uint8_t (*pFunType_oneArg)(uint8_t);
typedef uint8_t (*pFunType_twoArg)(uint8_t, uint8_t);

typedef struct  
{
    uint8_t (*pFunAND)(uint8_t, uint8_t);
    uint8_t (*pFunOR)(uint8_t, uint8_t);
    uint8_t (*pFunXOR)(uint8_t, uint8_t);
    uint8_t (*pFunNOT)(uint8_t);
    uint8_t (*pFunArr[3])(uint8_t, uint8_t);
}structOfFunctionPointers_t;

pFunType_oneArg FunctionPointerInAndOutTest1(pFunType_oneArg inPfun);
pFunType_twoArg FunctionPointerInAndOutTest2(pFunType_twoArg pFunIN[], uint8_t maxn,uint8_t n);

void CallFunctionPointerTest1(void);
void CallFunctionPointerTest2(void);

#endif // _FUNCTION_POINTERS1_H
