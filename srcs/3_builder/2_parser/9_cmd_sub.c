#include "parser.h"
#include "parser_item_stack.h"
#include "parser_here_stack.h"
#include "token.h"
#include "cst.h"

void	parser_cmd_sub_init(
			const t_parser *main_parser,
			t_parser *cmd_sub_parser)
{
	parser_item_stack_init(&cmd_sub_parser->item_stack);
	parser_here_stack_init(&cmd_sub_parser->here_stack);
	token_pool_init(&cmd_sub_parser->token_pool);
	cmd_sub_parser->cst = NULL;
	cmd_sub_parser->qualifiers = main_parser->qualifiers;
	cmd_sub_parser->lookahead_id = 0;
	cmd_sub_parser->lookahead_raw_symbol = SYM_NONE;
	cmd_sub_parser->lookahead_symbol = SYM_NONE;
	cmd_sub_parser->function_body_depth = 0;
	cmd_sub_parser->assignment_disabled = false;
	cmd_sub_parser->expansion_disabled = false;
	cmd_sub_parser->search_cmd_sub_end = true;
	cmd_sub_parser->cmd_sub_end_index = 0;
}

void	parser_cmd_sub_free(t_parser *cmd_sub_parser)
{
	parser_item_stack_free(&cmd_sub_parser->item_stack);
	parser_here_stack_free(&cmd_sub_parser->here_stack);
	token_pool_free(&cmd_sub_parser->token_pool);
	cst_node_free(&cmd_sub_parser->cst);
	cmd_sub_parser->lookahead_id = 0;
	cmd_sub_parser->lookahead_raw_symbol = SYM_NONE;
	cmd_sub_parser->lookahead_symbol = SYM_NONE;
	cmd_sub_parser->function_body_depth = 0;
	cmd_sub_parser->assignment_disabled = false;
	cmd_sub_parser->expansion_disabled = false;
	cmd_sub_parser->search_cmd_sub_end = true;
	cmd_sub_parser->cmd_sub_end_index = 0;
}
