#include "parser_item_stack.h"
#include "parser_here_stack.h"
#include "parser.h"
#include "token.h"
#include "cst.h"
#include "shell.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	parser_init(t_parser *parser)
{
	assert(parser != NULL);
	parser_item_stack_init(&parser->item_stack);
	parser_here_stack_init(&parser->here_stack);
	token_pool_init(&parser->token_pool);
	parser->cst = NULL;
	parser->lookahead_id = 0;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	parser->search_cmd_sub_end = false;
	parser->cmd_sub_end_index = 0;
	scanner_init(&parser->scanner);
	parser->machine = NULL;
}

t_error	parser_load(
			t_parser *parser,
			t_scanner *parent_scanner,
			t_scan_mode mode)
{
	t_error	err;

	assert(parser != NULL);
	parser_item_stack_init(&parser->item_stack);
	parser_here_stack_init(&parser->here_stack);
	token_pool_init(&parser->token_pool);
	parser->cst = NULL;
	parser->lookahead_id = 0;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	parser->search_cmd_sub_end = (mode == SCAN_MODE_CMD_SUB);
	parser->cmd_sub_end_index = -1;
	err = scanner_load(&parser->scanner, parent_scanner, parser, mode);
	if (err.type)
		return (err);
	return (shell_get_lr_machine(&parser->machine));
}

void	parser_clear(t_parser *parser)
{
	assert(parser != NULL);
	scanner_clear(&parser->scanner);
	parser_item_stack_clear(&parser->item_stack);
	parser_here_stack_clear(&parser->here_stack);
	token_pool_clear(&parser->token_pool);
	cst_node_free(&parser->cst);
	parser->cst = NULL;
	parser->lookahead_id = 0;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	parser->search_cmd_sub_end = false;
	parser->cmd_sub_end_index = 0;
}

void	parser_free(t_parser *parser)
{
	assert(parser != NULL);
	scanner_free(&parser->scanner);
	parser_item_stack_free(&parser->item_stack);
	parser_here_stack_free(&parser->here_stack);
	token_pool_free(&parser->token_pool);
	cst_node_free(&parser->cst);
	parser->cst = NULL;
	parser->lookahead_id = 0;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	parser->search_cmd_sub_end = false;
	parser->cmd_sub_end_index = 0;
}

void	parser_cmd_sub_free(t_parser *parser)
{
	parser_free(parser);
}
