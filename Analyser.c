#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack/stack.h"
#include "libMath/math.h"

#define SIZE_NUM_MAX 15+1
enum {DELIMITADOR=1, NUMERO, OPERATOR};

char *expression;

void getExpression(FILE *fin) {
    char ch;
    int index = 0;
    if ((expression = (char *) malloc(128)) == NULL) /*Arrumar Isto aqui*/
        return;
    printf("> ");
    
    while ((ch = fgetc(fin)) != '\n')  
        expression[index++] = ch;
    expression[index] = '\0';
}

int processExp(void) {
    
    if (!*expression) return -1;    
    while (isspace(*expression)) expression++;    
    if (strchr("()=+-*/^%", *expression))        
        return DELIMITADOR;       
    if (str_isNumber(*expression)) 
        return NUMERO;    
    return -1;
}

double operation(double a, char op, double b) {
    switch (op) {
        case '+':
            return a + b;
        case '-': 
            return a - b;
        case '*': 
            return a * b;
        case '/':
            return b / a;
    }
    return 0;
}

void processExpression(Stack *values, Stack *Operators) {
    while (Operators->node_ini != NULL && (*(char *) (Operators->node_ini->data)) != '(') {
        double val = *((double *) (values->node_ini)->data);
        pop(values);
        double val2 = *(double *) (values->node_ini)->data;
        pop(values);
        char op =  *(char *) (Operators->node_ini->data);
        pop(Operators);
        push(values, operation(val, op, val2));
    }
}

uint8_t precedence(char op){
    if (op == '+'|| op == '-')
        return 1;
    if (op == '*'|| op == '/')
        return 2;
    return 0;
}

void delimiterProcess(Stack *stackValues, Stack *stackOperators) {
    static uint8_t state = 0;
    if (*expression == '(') 
        state = 1;
    else if (*expression == ')' && state == 1) {
        processExpression(stackValues, stackOperators);
        state = 0;
        if (stackOperators->node_ini != NULL)
            pop(stackOperators);
        expression++;
        return;
    }
    else {
        while (stackOperators->node_ini != NULL 
            && precedence( *(char *) stackOperators->node_ini->data) >= precedence(*expression)) 
            processExpression(stackValues, stackOperators);
        }
    push(stackOperators, *expression);
}

void numberProcess(Stack *stackValues) {
    uint8_t index = 0;
    char num[SIZE_NUM_MAX];
    while(str_isNumber(*expression))
        num[index++] = *expression++;                
    num[index] = '\0';
    push(stackValues, math_atof(num));
}

void Analyser(FILE *fin, FILE  *fout) {
    int8_t type_token, state = 0;
    Stack *stackValues = initStack();
    Stack *stackOperators = initStack(); 
    double result;
    char *expAux;
    do {
        getExpression(fin);
        expAux = expression;
        while ((type_token = processExp()) > 0) {
            switch (type_token) {
                case DELIMITADOR:
                    delimiterProcess(stackValues, stackOperators);
                break;
                case NUMERO:                        
                    numberProcess(stackValues);
                    continue;
                break;
                default: exit(1);
            }
            expression++;
        }
        while (stackOperators->node_ini != NULL) 
            processExpression(stackValues, stackOperators);        
        fprintf(fout, "> %s = %.2f\n", expAux, *(double *) stackValues->node_ini->data);
        pop(stackValues);
        free(expAux);
    } while (strcmp(expAux, "exit") != 0);
}

int main(int argc, char **argv) {
    if (argc > 2) 
        return 0;
    FILE *fin = stdin;
    FILE *fout = stdout;
    if (argc > 1) {
        if ((fin = fopen(argv[1], "rt")) == NULL)
            return 0;
        if ((fout = fopen("result.txt", "wt")) == NULL)
            return 0; 
    } 
    Analyser(fin, fout);
    return 0;
}