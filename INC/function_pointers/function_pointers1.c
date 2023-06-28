#include "function_pointers1.h"

pFunType_oneArg FunctionPointerInAndOutTest1(pFunType_oneArg inPfun)
{
    pFunType_oneArg pFunNOT;
    pFunNOT = inPfun;

    return pFunNOT;
}
pFunType_twoArg FunctionPointerInAndOutTest2(pFunType_twoArg pFunIN[], uint8_t maxn,uint8_t n)
{
    pFunType_twoArg pFun; 
    if(n > maxn) 
        n = 0;

    pFun = *(pFunIN + n);

    return pFun;
}
void CallFunctionPointerTest1(void)
{
    uint8_t retval, i;
    pFunType_twoArg pFunTwoArgs;
    structOfFunctionPointers_t myFunctionPointerStruct;

    myFunctionPointerStruct.pFunAND = (pFunType_twoArg)&LogicalAND;
    myFunctionPointerStruct.pFunOR  = (pFunType_twoArg)&LogicalOR;
    myFunctionPointerStruct.pFunXOR = (pFunType_twoArg)&LogicalXOR;
    myFunctionPointerStruct.pFunNOT = FunctionPointerInAndOutTest1((pFunType_oneArg)&LogicalNOT);

    myFunctionPointerStruct.pFunArr[0] = (pFunType_twoArg)&LogicalAND;
    myFunctionPointerStruct.pFunArr[1] = (pFunType_twoArg)&LogicalOR;
    myFunctionPointerStruct.pFunArr[2] = (pFunType_twoArg)&LogicalXOR;    

    retval = (*myFunctionPointerStruct.pFunAND)(0x1F, 0xF1);
    printf("Return value: %x \n", retval);

    retval = (*myFunctionPointerStruct.pFunOR)(0x1F, 0xF1);
    printf("Return value: %x \n", retval);

    for(i=0; i<3; i++)
    {
        retval = (*myFunctionPointerStruct.pFunArr[i])(0x1F, 0xF1);
        printf("Arr Return value: %x \n", retval); 
    }
}
void CallFunctionPointerTest2(void)
{
    uint8_t retval, i;
    pFunType_twoArg pFunTwoArgs;
    structOfFunctionPointers_t myFunctionPointerStruct;

    myFunctionPointerStruct.pFunAND = (pFunType_twoArg)&LogicalAND;
    myFunctionPointerStruct.pFunOR  = (pFunType_twoArg)&LogicalOR;
    myFunctionPointerStruct.pFunXOR = (pFunType_twoArg)&LogicalXOR;
    myFunctionPointerStruct.pFunNOT = FunctionPointerInAndOutTest1((pFunType_oneArg)&LogicalNOT);

    myFunctionPointerStruct.pFunArr[0] = (pFunType_twoArg)&LogicalAND;
    myFunctionPointerStruct.pFunArr[1] = (pFunType_twoArg)&LogicalOR;
    myFunctionPointerStruct.pFunArr[2] = (pFunType_twoArg)&LogicalXOR; 

    printf("Function pointer in and out test: \n");
    retval = (*myFunctionPointerStruct.pFunNOT)(0x77);
    printf("Return value: %x \n", retval);

    printf("Array of function pointer and return function pointer: \n");
    for(i=0; i<3; i++)
    {
        pFunTwoArgs = FunctionPointerInAndOutTest2(myFunctionPointerStruct.pFunArr, 2, i);
        retval = (*pFunTwoArgs)(0x00, 0xFF); 
        printf("i= %x Function return pointer to function: %x \n", i,retval); 
    }   
}