#ifndef PARSER_TYPE_H
# define PARSER_TYPE_H

# include "qualifiers_type.h"
# include "parser_stack_type.h"
# include "token.h"

typedef struct s_parser
{
	t_parser_stack	stack;
	t_token_pool	token_pool;
	size_t			lookahead_id;
	t_symbol		lookahead_raw_symbol;
	t_symbol		lookahead_symbol;
	t_cst_node		*cst;
	t_qualifier		*qualifiers;	// [lr_state]
	size_t			function_body_depth;
	bool			assignment_disabled;
	bool			expansion_disabled;
	bool			must_read_heredoc;
}	t_parser;

#endif
