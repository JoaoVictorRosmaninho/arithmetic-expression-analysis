#ifndef ANALYZER_H
# define ANALYZER_H

#include "../libs/libft/includes/libft.h"

typedef enum {
  TREE,
  INFIX,
  POSTIX
} e_representations

typedef enum {
  PLUS,
  MINUS,
  MULT,
  DIV,
  DIV_INTEGER,
  EXPO,
  OPERAND
} e_node_type;



typedef struct s_node {
  e_token_type type;
  char *content;
  union {
    struct s_node *left;
    struct s_node *right;
  } as;
} t_bree_node;

typedef struct {
  char *prev;
  char *curr;
  unsigned char error;
} t_analyser;

#endif


