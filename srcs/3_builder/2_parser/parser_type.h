#ifndef PARSER_TYPE_H
# define PARSER_TYPE_H

# include "parser_item_stack_type.h"
# include "parser_here_stack_type.h"
# include "token.h"
# include "scanner.h"
# include "lr_machine_type.h"

typedef struct s_parser
{
	t_scanner			scanner;
	const t_lr_machine	*machine;				// borrowed
	t_parser_item_stack	item_stack;
	t_parser_here_stack	here_stack;
	t_token_pool		token_pool;
	size_t				lookahead_id;
	t_symbol			lookahead_raw_symbol;
	t_symbol			lookahead_symbol;
	t_cst_node			*cst;					// owned
	size_t				function_body_depth;
	bool				assignment_disabled;
	bool				expansion_disabled;
	bool				search_cmd_sub_end;
	ssize_t				cmd_sub_end_index;
}	t_parser;

#endif
