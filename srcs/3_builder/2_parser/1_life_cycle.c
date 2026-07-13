#include "parser_priv.h"
#include "parser_stack.h"
#include "parser.h"
#include "token.h"
#include "cst.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	parser_init(t_parser *parser)
{
	assert(parser != NULL);
	parser_stack_init(&parser->stack);
	token_pool_init(&parser->token_pool);
	parser->cst = NULL;
	parser->qualifiers = NULL;
	parser->lookahead_id = 0;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	parser->must_read_heredoc = false;
}

void	parser_clear(t_parser *parser)
{
	parser_stack_clear(&parser->stack);
	token_pool_clear(&parser->token_pool);
	cst_node_free(&parser->cst);
	parser->cst = NULL;
	parser->lookahead_id = 0;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	parser->must_read_heredoc = false;
}

void	parser_free(t_parser *parser)
{
	assert(parser != NULL);
	parser_stack_free(&parser->stack);
	token_pool_free(&parser->token_pool);
	cst_node_free(&parser->cst);
	free(parser->qualifiers);
	parser_init(parser);
}
