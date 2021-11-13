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
int deep (struct Node *tree);
void no_child (struct Node *tree);
int is_balanced (struct Node *tree);

int main () {
    struct Node *tree = NULL;
    int x = 1;
    scanf ("%d", &x);
    while (x != 0) {
        tree = tree_add (tree, x);
        scanf ("%d", &x);
    }
    // tree_print (tree);
    // printf ("\n");
    // printf ("%d", deep (tree));
    // no_child (tree);
    if (is_balanced (tree) == 1) {
        printf ("YES\n");
    }
    else {
        printf ("NO\n");
    }
    tree_destroy (tree);
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

int deep (struct Node *tree) {
    if (!tree) {
        return 0;
    }
    else {
        int left = deep (tree -> left);
        int right = deep (tree -> right);
        return (left > right) ? left + 1 : right + 1;
    }
}

void no_child (struct Node *tree) {
    if (tree -> left == NULL && tree -> right == NULL) {
        printf ("%d ", tree -> val);
    }
    else {
        if (tree -> left) {
            no_child (tree -> left);
        }
        if (tree -> right) {
            no_child (tree -> right);
        }
    }
}

int is_balanced (struct Node *tree) {
    if (!tree) {
        return 1;
    }
    int left = deep (tree -> left);
    int right = deep (tree -> right);
    if (left - right >= -1 && left - right <= 1) {
        if (is_balanced (tree -> left) * is_balanced (tree -> right) == 1) {
            return 1;
        }
    }
    return 0;
}