
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
		token->type    = ft_lexer_get_type(lexer);
		return token;
	}
	return NULL;
}

void advance_to_next_token(t_parser_context *context) {	
	context->prev = context->current;
	context->current = build_token(context->lexer);
}

t_token *ft_current_token(t_parser_context *context) {
	return context->current;
}

t_token *ft_prev_token(t_parser_context *context) {
	return content->prev;
}

void free_token(token *token)
{
	if (token) {
		free(token->content);
		free(token);
	}
}

t_bree_node *ft_build_node(t_token *token)
{
	t_bree_node *new_node;

	if ((new_node = (t_bree_node *)ft_calloc(1, sizeof(t_btree_node))) == NULL) 
		return (NULL);
	if (!token) return (new_node);
	new_node->as.left  = NULL;
	new_node->as.right = NULL;
	new_node->value = ft_atoi(token->content);
	new_node->type = token->type;
	free_token(token);
	return (new_node);
}


t_bree_node ft_build_exp(t_bree_node *l, t_btree_node *r) {
	t_bree_node *node = ft_build_node(NULL);

	node->as.left  = l;
	node->as.right = r;
	node->type 	   = r->type;
	node->value    = 0;

	return (node);
}

t_btree_node *build_tree(t_parser_context *context) {
	t_token 	*token = NULL;
	t_bree_node	*node  = NULL;
	while ((token = ft_current_token(context)) != NULL) {
		advance_to_next_token(context);
		node  = ft_build_node(token);
		t_btree_node *right = ft_build_node(ft_current_token(context));
 		node = ft_build_exp(node, right);
	}
	return (node);
}


t_btree_node *ft_analyzer(char *expression) {
	t_analyser lexer = {
		.curr = expression,
		.prev = expression
	}
	return parse_exp(&lexer);
}
