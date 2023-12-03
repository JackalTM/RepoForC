#include "_tree_object_inc.h"
#ifdef _TREE_OBJECT_EQUASION_H

// Double include protection
#ifndef TREE_OBJECT_EQUASION_H
#define TREE_OBJECT_EQUASION_H

#include <stdlib.h>
#include <stdio.h>

#include "tree_object_definitions.h"

#define TREE_OBJECT_EQUASION_DEBUG_PRINT

typedef struct treeElement_t
{// Structure for conecting treeobject
    struct treeElement_t* pTreeElemLeft;
    struct treeElement_t* pTreeElemRigh;

    double value;
    char operation;
    char calculationState;
}treeElement_t;

typedef struct 
{// Structure for diagnose self call amount
    unsigned short int nCalls;
    unsigned short int errorOnCall;
}treeElemControl_t;

#define MAX_AMOUNT_OF_CALLS 0x20
treeElement_t   TreeObjCreateOperation(char op);
treeElement_t   TreeObjCreateValue(double value);
treeElement_t*  TreeObjNewNodeInTree(treeElement_t newNode);

void TreeObjPrintAllTree(treeElement_t* pTreeElement,       treeElemControl_t* pTreeElemControl,    unsigned int level);
void TreeObjEvaluateTree(treeElement_t* pTreeElement,       treeElemControl_t* pTreeElemControl);
void TreeObjReliseAllMemory(treeElement_t* pTreeElement,    treeElemControl_t* pTreeElemControl);


void TreeObjParse(treeElement_t** ppTreeElement, char pInputChar[], char* pIdx);

#endif // TREE_OBJECT_EQUASION_H
#endif // _TREE_OBJECT_EQUASION_H