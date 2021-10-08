
#ifndef STACK_HEADER
# define STACK_HEADER
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>

# define push(stack, x) _Generic((x), int: addInt, char *: addString, char:addChar,  double: addDouble, float: addFloat)(stack, x)


enum {INTEGER, STRING, CHAR,  FLOAT, DOUBLE};

typedef struct node {
    void *data;
    struct node *next;
    uint8_t type;
}Node;

typedef struct {
    Node *node_ini;
    Node *node_end;
} Stack;

Node *makeNode(void *dataToStore, uint8_t type);
void addInOrder(Stack *stack, void *dataToStore, uint8_t type);
void pop(Stack *stack);
void addInt(Stack *stack, int num);
void addString(Stack *stack, char *str);
void addFloat(Stack *stack, float num);
void addDouble(Stack *stack, double num);
void addChar(Stack *stack, char ch);
Stack *initStack(void);
void display(Stack *stack);

#endif
