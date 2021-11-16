#include <stdio.h>
#include <stdlib.h>

typedef int Data;

struct Node {
    Data val;           // данные в узле
    int freq;
    struct Node *left;  // левый ребенок
    struct Node *right; // правый ребенок
};
struct Queue {
    int capacity; //вместимость
    int size;   //номер элемента, в который нужно положить
    struct Node **data;

};

struct Node *tree_add (struct Node *tree, Data x);
void tree_print (struct Node *tree);
void tree_destroy (struct Node *tree);
int deep (struct Node *tree);
void no_child (struct Node *tree);
int is_balanced (struct Node *tree);
void tree_print_freq (struct Node *tree);
void tree_print_width (struct Queue *queue, struct Node *tree);
struct Queue *queue_add (struct Queue *queue, struct Node *tree);
void queue_recopy (struct Node **oldData, struct Node **newData, int size);
void queue_destroy (struct Queue *queue);
void queue_top (struct Queue *queue);
void queue_shift (struct Queue *queue);
void queue_print (struct Queue *queue);


int main () {
    struct Node *tree = NULL;
    int x = 1;
    scanf ("%d", &x);
    while (x != 0) {
        tree = tree_add (tree, x);
        scanf ("%d", &x);
    }

    struct Queue *queue = NULL;
    queue = queue_add (queue, tree);
    if (queue -> data) {
    }
    tree_print_width (queue, tree);
    queue_destroy (queue);
    tree_destroy (tree);
    return 0;
}

struct Node *tree_add (struct Node *tree, Data x) {
    if (!tree) {
        struct Node *tree = (struct Node *) calloc (1, sizeof (*tree));
        tree -> val = x;
        tree -> freq = 1;
        return tree;
    }

    if (x < tree -> val) {
       tree -> left =  tree_add (tree -> left, x);
    }
    else if (x > tree -> val) {
       tree -> right = tree_add (tree -> right, x);
    }
    else {
        tree -> freq += 1;
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

void tree_print_freq (struct Node *tree) {
    if (tree -> left) {
        tree_print_freq (tree -> left);
    }
    printf ("%d %d\n", tree -> val, tree -> freq);
    // printf ("hello\n"); 
    if (tree -> right) {
        tree_print_freq (tree -> right);
    }
}

void tree_print_width (struct Queue *queue, struct Node *tree) {
    if ((queue -> data)) {
        if ((queue -> data)[0]) {
            if ((queue -> data)[0] -> left) {
                queue = queue_add (queue, (queue -> data)[0] -> left);
            }

            if ((queue -> data)[0] -> right) {
                queue = queue_add (queue, (queue -> data)[0] -> right);
            }
            queue_top (queue);
            tree_print_width (queue, tree);
        }
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

struct Queue *queue_add (struct Queue *queue, struct Node *tree) {

    if (queue == NULL) {
        struct Queue *queue = (struct Queue *) calloc (1, sizeof (queue));
        queue -> capacity = 4;
        queue -> size = 0;
        queue -> data = (struct Node **) calloc (queue -> capacity, sizeof (struct Node *));
        (queue -> data)[0] = tree;
        queue -> size++;
        return queue;
    }

    if (queue -> size == queue -> capacity) {
        queue -> capacity *= 4;
        struct Node **oldData = queue -> data;
        queue -> data = (struct Node **) calloc (queue -> capacity, sizeof (struct Node *));
        queue_recopy (oldData, queue -> data, queue -> size);
        free (oldData);
    }

    (queue -> data)[queue -> size] = tree;
    queue -> size++;
    return queue;
}

void queue_recopy (struct Node **oldData, struct Node **newData, int size) {
    for (int i = 0; i < size; i++) {
        newData[i] = oldData[i];
    }
}

void queue_destroy (struct Queue *queue) {
    for (int i = 0; i < queue -> size; i++) {
        free ((queue -> data)[i]);
    }
    free (queue -> data);
    free (queue);
}

void queue_top (struct Queue *queue) {
    printf ("%d ", ((queue -> data)[0]) -> val);
    queue -> size -= 1;
    queue_shift (queue);
    (queue -> data)[queue -> size] = NULL;
}

void queue_shift (struct Queue *queue) {
    free ((queue -> data)[0]);
    for (int i = 0; i < queue -> size; i++) {
        (queue -> data)[i] = (queue -> data)[i + 1];
    }
}

void queue_print (struct Queue *queue) {
    printf ("Print queue:\n");
    if (queue != NULL) {
        for (int i = 0; i < queue -> size; i++) {
            printf ("%d ", (queue -> data)[i] -> val);
        }
    }
    
    printf ("-------------\n");
}