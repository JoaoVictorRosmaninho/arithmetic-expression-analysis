#include "../includes/analyser.h"



int main(int argc, char *argv[])
{
  (void) argc;
  (void) argv;

  char *expression = get_next_line(0);

  ft_analyzer(expression, POSTFIX);

  free(expression);
}
