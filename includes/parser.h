#ifndef PARSER_H
# define PARSER_H

# include "libft.h"		// t_btree_node
# include "lexer.h"		// t_token

typedef struct s_parser
{
	size_t			word_count;	// Count of words already presents in current command
	t_btree_node	*ast_root;
	t_token			*stack;
	// TODO
}	t_parser;

#endif
