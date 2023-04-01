
#include "../includes/analyser.h"

void next_token(t_analyser *lexer) {
	unsigned char flag = 1;

	lexer->prev = lexer->curr;
	while (1) {
		if (ft_isdigit(*lexer->curr)) {
			while (ft_isdigit(lexer->curr))
				lexer->curr++;
			break;
		} else if (ft_isoperator(*lexer->curr)) {
			lexer->curr++;
			break ;
		}
		lexer->curr++;
	}
	if (is_at_end(lexer) || lexer_curr_is_space(lexer))
		lexer->curr = NULL;
}

t_token *build_token(t_analyser *lexer) {
	next_token(lexer);

	if (lexer->curr != NULL)  {
		t_token *token;
		if ((token = ft_calloc(1, sizeof(token))) != NULL) 
			return (NULL);
		token->content = ft_strndup(token->prev, token->curr - token->prev);
		token->type = ft_lexer_get_type(lexer);
		return token;
	}
	return NULL;
}


void free_token(token *token)
{
	if (token) {
		free(token->content);
		free(token);
	}
}

// 2  + 2 + 2
t_btree_node *build_tree(t_analyser *lexer) {
	t_lstnew	*operators = ft_lstnew();
	t_token 	*token = NULL;
	
	while ((token = build_token(lexer)) != NULL) {
		if (token->type != OPERAND) {

		}
		ft_lstadd_back(operators, ft_lstnew_node(mk_int_content(ft_atoi(token->content))))
		free_token(token);
	}


}


t_btree_node *ft_analyzer(char *expression) {
	t_analyser lexer = {
		.curr = expression,
		.prev = expression
	}

	
	return parse_exp(&lexer);
}
