#include "_tree_object_inc.h"

#ifdef _TREE_OBJECT_EXERCISE_H

#ifndef TREE_OBJECT_EXERCISE_H
#define TREE_OBJECT_EXERCISE_H

#include <stdio.h>
#include <stdlib.h>

#define NO_OP ' '

typedef struct tree_el
{
    char op;
    double val;
    int is_val_computed;

    struct tree_el *left;
    struct tree_el *right;
} tree_el;

tree_el create_op(char op);
tree_el create_val(double val);
tree_el* new_node(tree_el el);

void print_tree(tree_el* el, int level);
void evaluate(tree_el* el);
void clear_tree(tree_el* tree);
void parse(tree_el **el, char* input, int *input_ptr);

void CALL_main_test(char* pStr);

#endif // TREE_OBJECT_EXERCISE_H
#endif // _TREE_OBJECT_EXERCISE_H