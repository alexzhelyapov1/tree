#include <stdio.h>
#include <stdlib.h>

typedef int Data;

struct Node {
    Data val;            // данные в узле
    struct Node * left;  // левый ребенок
    struct Node * right; // правый ребенок
};

struct Node *tree_add (struct Node *tree, Data x);
void tree_print (struct Node *tree);
void tree_destroy (struct Node *tree);

int main () {
    
    return 0;
}

struct Node *tree_add (struct Node *tree, Data x) {
    if (!tree) {
        struct Node *tree = (struct Node *) calloc (1, sizeof (*tree));
        tree -> val = x;
        return tree;
    }

    if (x < tree -> val) {
       tree -> left =  tree_add (tree -> left, x);
    }
    else if (x > tree -> val) {
       tree -> right = tree_add (tree -> right, x);
    }
    return tree;
}

void tree_print (struct Node *tree) {
    if (tree -> left) {
        tree_print (tree -> left);
    }
    printf ("%d ", tree -> val);
    if (tree -> right) {
        tree_print (tree -> right);
    }
}

void tree_destroy (struct Node *tree) {
    if (tree) {
        tree_destroy (tree -> left);
        tree_destroy (tree -> right);
        free (tree);
    }
}