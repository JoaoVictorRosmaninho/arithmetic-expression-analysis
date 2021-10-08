


#include "stack.h"


Node *makeNode(void *dataToStore, uint8_t type) {
    Node *temp;
    if ((temp = calloc(1, sizeof(Node))) == NULL) 
        return NULL;
    temp->data = dataToStore;
    temp->type = type;
    return temp;
}

void addInOrder(Stack *pilha, void *dataToStore, uint8_t type) {
    Node *temp = makeNode(dataToStore, type);
    if (pilha->node_ini == NULL) {
        pilha->node_end = pilha->node_ini = temp;
        return;
    }
    temp->next = pilha->node_ini;
    pilha->node_ini = temp;
    return ;
}
void pop(Stack *pilha) {
    Node *temp = pilha->node_ini;
    pilha->node_ini = pilha->node_ini->next;
    free(temp);
}

void addInt(Stack *stack, int num) {
    int *ptr = (int *) malloc(sizeof(int));
    *ptr = num;
    addInOrder(stack, (void *) ptr, INTEGER);
}

void addString(Stack *stack, char *str) {
    addInOrder(stack, (void *) strdup(str), STRING);
}

void addFloat(Stack *stack, float num) {
    float *ptr = (float *) malloc(sizeof(float));
    *ptr = num;
    addInOrder(stack, (void *) ptr, FLOAT);
}

void addDouble(Stack *stack, double num) {
    double *ptr = (double * )malloc(sizeof(double));
    *ptr = num;
    addInOrder(stack, (void *) ptr, DOUBLE);
}

void addChar(Stack *stack, char ch) {
    char *ptr = (char *)malloc(sizeof(char));
    *ptr = ch;
    addInOrder(stack, (void *) ptr, CHAR);
}


Stack *initStack(void) {
    return (Stack *) calloc(1, sizeof(Stack));
}

void display(Stack *pilha) {
    if (pilha->node_ini == NULL) {
        puts("Stack vazia");
        return;
    }    
    Node *temp = pilha->node_ini;
    char *delimiter = ", ";
    putchar('[');
    while (temp != NULL) {
        if (temp->next == NULL)
            delimiter = "";
        switch (temp->type) {
            case INTEGER:
                printf("%d%s", *(int *) temp->data, delimiter);
            break;
            case STRING:
                printf("%s%s", (char *) temp->data, delimiter);
            break;
            case CHAR:
                printf("%c%s", *(char *) temp->data, delimiter);
            break;
            case FLOAT:
                printf("%.2f%s", *(float *) temp->data, delimiter);
            break;
            case DOUBLE:
                printf("%.2f%s", *(double *) temp->data, delimiter);
            break;
            default:
                printf("%p%s", temp->data, delimiter);
        }
        temp = temp->next;
    }
    putchar(']');
    putchar('\n');
}
