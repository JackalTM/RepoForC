#include "_tree_object_inc.h"
#ifdef _TREE_OBJECT_EQUASION_H

// Double include protection
#ifndef TREE_OBJECT_EQUASION_H
#define TREE_OBJECT_EQUASION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree_object_definitions.h"

#define MAX_AMOUNT_OF_CALLS 0x20
#define WRONG_VALUE (char)0xFF
//#define TREE_OBJECT_EQUASION_DEBUG_PRINT

typedef struct treeElement_t
{// Structure for conecting treeobject.
    struct treeElement_t* pTreeElemLeft;
    struct treeElement_t* pTreeElemRigh;

    double  value;
    char    operation;
    char    calculationState;
}treeElement_t;

typedef struct 
{// Structure for recursion call.
 // Posibility for infinite call itself.
    unsigned short int nCalls;
    unsigned short int nMAX;
    unsigned short int exitOnCall;
}treeElemControl_t;

typedef struct 
{// Structure for parse object create control.
 // Posibility for infinite call itself.
    char* pStr;
    unsigned short int nMax;
    unsigned short int idx;
}treeElemParse_t;

treeElement_t   TreeObjCreateOperation(char op);
treeElement_t   TreeObjCreateValue(double value);
treeElement_t*  TreeObjNewNodeInTree(treeElement_t newNode);

void TreeObjPrintAllTree(       treeElement_t* pTreeElement,    treeElemControl_t* pTreeElemControl,    unsigned int level);
void TreeObjEvaluateTree(       treeElement_t* pTreeElement,    treeElemControl_t* pTreeElemControl);
void TreeObjReliseAllMemory(    treeElement_t* pTreeElement,    treeElemControl_t* pTreeElemControl);

void TreeObjParse_Alpha(treeElemParse_t*  pTreeElemParse);
void TreeObjParse_Beta(treeElement_t** ppTreeElement, treeElemParse_t*  pTreeElemParse);
void TreeObjParse_V0(treeElement_t** ppTreeElement, treeElemParse_t*  pTreeElemParse);

#endif // TREE_OBJECT_EQUASION_H
#endif // _TREE_OBJECT_EQUASION_H