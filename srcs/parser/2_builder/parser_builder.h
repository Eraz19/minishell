#ifndef PARSER_BUILDER_H
# define PARSER_BUILDER_H

# include "lexer.h"
# include "parser.h"

typedef struct s_ast_node
{
	t_token	*root;
	t_token	*left;
	t_token	*right;
	// TODO
}	t_ast_node;

typedef struct s_parser_token
{
	t_token			*token;
	t_btree_node	*ast_node;
	// TODO
}	t_parser_token;

void	shift(t_parser *parser, t_token *token);	// Add a token to the stack
bool	reduce(t_parser *parser, t_list tokens);	// Merge tokens into a new one and create the corresponding subtree into the AST

#endif
