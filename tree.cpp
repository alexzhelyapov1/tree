#include <stdio.h>
#include <stdlib.h>

typedef int Data;

enum Balance {
    DISBALANCED = -1,
    BALANCED_XZ,
    BALANCED,
};

struct Node {
    Data val;           // данные в узле
    int freq;
    struct Node *left;  // левый ребенок
    struct Node *right; // правый ребенок
    int deep;           // глубина дерева, где данная вершина - корень
    int balanced;       // сбалансированно ли дерево
};
struct Queue {
    int capacity;   //вместимость
    int size;       //номер элемента, в который нужно положить
    struct Node **data;

};

struct Node *tree_add (struct Node *tree, Data x); // добавляет элемент в дерево
void tree_print (struct Node *tree);    // печатает дерево в порядке возрастания
void tree_destroy (struct Node *tree);  // уничтожает дерево, очищает память
int deep (struct Node *tree);           // заполняет дерево параметрами глубины
void no_child (struct Node *tree);      // печатает листья
int is_balanced (struct Node *tree);    // проверяет, сдабалнированно ли дерево
void tree_print_freq (struct Node *tree);                                   // печатает дерево с параметром частоты каждой вершины
void tree_print_width (struct Queue *queue, struct Node *tree);             // печатает в ширину, по уровням
struct Queue *queue_add (struct Queue *queue, struct Node *tree);           // добавляет очередь
void queue_recopy (struct Node **oldData, struct Node **newData, int size); // перекопирует в новую очередь
void queue_destroy (struct Queue *queue);       // уничтожает очередь, освобождает память
void queue_top (struct Queue *queue);           // печатает и удаляет первый элемент
void queue_shift (struct Queue *queue);         // сдвигает очередь на 1 вперед
void queue_print (struct Queue *queue);         // печатает очередь


int main () {
    struct Node *tree = NULL;
    int x = 1;
    while ((scanf ("%d", &x) == 1) && x != 0) {
        tree = tree_add (tree, x);
    }

    deep (tree);
    if (is_balanced (tree) == BALANCED) {
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
        tree -> freq = 1;
        tree -> balanced = BALANCED_XZ;
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
        tree -> deep = (left > right) ? left + 1 : right + 1;
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
        return BALANCED;
    }
    if (tree -> balanced == BALANCED) {
        return BALANCED;
    }
    else if (tree -> balanced == DISBALANCED) {
        return DISBALANCED;
    }

    int left = 0;
    int right = 0;
    if (tree -> left) {
        left = tree -> left -> deep;
    }
    if (tree -> right) {
        right = tree -> right -> deep;
    }

    if (left - right >= -1 && left - right <= 1 && is_balanced (tree -> left) == BALANCED && is_balanced (tree -> right) == BALANCED) {
        tree -> balanced = BALANCED;
        return BALANCED;
    }
    tree -> balanced = DISBALANCED;
    return DISBALANCED;
}

struct Queue *queue_add (struct Queue *queue, struct Node *tree) {

    if (queue == NULL) {
        // queue = (struct Queue *) calloc (1, sizeof (struct Queue));
        struct Queue *queue1 = (struct Queue *) calloc (1, sizeof (*queue1));
        queue1 -> capacity = 4;
        queue1 -> size = 0;
        queue1 -> data = (struct Node **) calloc (queue1 -> capacity, sizeof (struct Node *));
        (queue1 -> data)[0] = tree;
        queue1 -> size++;
        return queue1;
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