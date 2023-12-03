#include "tree_object_exercise.h"

#ifdef _TREE_OBJECT_EXERCISE_H

tree_el create_op(char op)
{
    tree_el new_el = {op, 0, 0, NULL, NULL};
    return new_el;
}

tree_el create_val(double val)
{
    tree_el new_el = {NO_OP, val, 1, NULL, NULL};
    return new_el;
}

void print_tree(tree_el* el, int level)
{
    if (el==NULL)
        return;

    for (int i=0; i<level; i++)
    {
        printf(" ");
    }
    printf("|- ");

    if (el->op != NO_OP)
    {
        printf("%c\t", el->op);
    }

    if (el->is_val_computed)
    {
        printf("%.2f\n", el->val);
    }
    else
    {
        printf("?\n");
    }
    
    print_tree(el->left, level+1);
    print_tree(el->right, level+1);
}

void evaluate(tree_el* el)
{
    if (el==NULL)
        return;

    evaluate(el->left);
    evaluate(el->right);

    if (el->op != NO_OP)
    {
        double a = el->left->val;
        double b = el->right->val;
        double c;

        switch (el->op)
        {
            case '+': c = a + b; break;
            case '*': c = a * b; break;
            case '-': c = a - b; break;
            case '/': c = a / b; break;
        }

        el->val=c;
        el->is_val_computed=1;
    }
}

tree_el* new_node(tree_el el)
{
    tree_el *new_el = (tree_el*)malloc(sizeof(tree_el));
    *new_el = el;
    return new_el;
}

void clear_tree(tree_el* tree)
{
    if (tree==NULL)
        return;

    clear_tree(tree->left);
    clear_tree(tree->right);
    free(tree);
}

static int is_argument(char c)
{
    return (c>='0' && c<='9');
}

void parse(tree_el **el, char* input, int *input_ptr)
{
    char c = input[*input_ptr];
    printf("|char[%x] := %c| \n", *input_ptr, c);
    (*input_ptr)++;


    if (c==0)
        return;

    if (is_argument(c))
    {
        //printf(" |ARG= %c \n", c);
        *el = new_node(create_val(c-'0'));
    }
    else
    {
        //printf(" |OPR= %c \n", c);
        tree_el *new_el = new_node(create_op(c));
        parse(&(new_el->left), input, input_ptr);
        parse(&(new_el->right), input, input_ptr);
        *el = new_el;
    }
    
}

void CALL_main_test(char* pStr)
{
    tree_el *root;
    int input_ptr = 0;
    int result;
    
    printf("DEBUG parse: \n");
    parse(&root, pStr, &input_ptr);
    print_tree(root, 0);

    evaluate(root);

    result = root->val;

    clear_tree(root);
}

#endif // _TREE_OBJECT_EXERCISE_H