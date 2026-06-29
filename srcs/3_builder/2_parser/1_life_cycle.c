#include "parser_priv.h"
#include "parser.h"
#include "token.h"
#include "cst.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	parser_init(t_parser *parser)
{
	assert(parser != NULL);
	(void)vector_init(&parser->stack, sizeof(t_parser_stack_item), 0);
	(void)vector_init(&parser->tokens, sizeof(t_token), 0);
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

t_error	parser_reset(t_parser *parser)
{
	size_t	i;

	assert(parser != NULL);
	i = 0;
	while (i < parser->stack.len)
		parser_free_stack_item(
			&((t_parser_stack_item *)parser->stack.data)[i++]);
	parser->stack.len = 0;
	i = 0;
	while (i < parser->tokens.len)
		parser_free_token(&((t_token *)parser->tokens.data)[i++]);
	parser->tokens.len = 0;
	cst_node_free(&parser->cst);
	parser->cst = NULL;
	parser->lookahead_id = 0;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	parser->must_read_heredoc = false;
	return (error(ERR_NO));
}

void	parser_free_token(void *token)
{
	assert(token != NULL);
	token_free(token);
}

void	parser_free_stack_item(void *raw_item)
{
	t_parser_stack_item	*item;

	assert(raw_item != NULL);
	item = raw_item;
	cst_node_free(&item->cst_node);
}

void	parser_free(t_parser *parser)
{
	assert(parser != NULL);
	vector_free(&parser->stack, parser_free_stack_item);
	vector_free(&parser->tokens, parser_free_token);
	cst_node_free(&parser->cst);
	free(parser->qualifiers);
	parser_init(parser);
}
