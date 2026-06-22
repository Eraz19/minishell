#include "parser_priv.h"
#include "token.h"
#include <stdlib.h>

void	parser_init(t_parser *parser)
{
	parser_stack_init(&parser->stack);
	(void)vector_init(&parser->tokens, sizeof(t_token), 0);
	parser->cst = NULL;
	parser->qualifiers = NULL;
	parser->lookahead_id = 0;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
}

t_error	parser_reset(t_parser *parser)
{
	size_t	i;

	i = 0;
	while (i < parser->stack.len)
		parser_free_stack_item(&((t_parser_stack_item *)parser->stack.data)[i++]);
	parser->stack.len = 0;
	i = 0;
	while (i < parser->tokens.len)
		parser_free_token(&((t_token *)parser->tokens.data)[i++]);
	parser->tokens.len = 0;
	parser_cst_node_free(&parser->cst);
	parser->cst = NULL;
	parser->lookahead_id = 0;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	return (error(ERR_NO));
}

void	parser_free_token(void *token)
{
	token_free(token);
}

void	parser_free_stack_item(void *raw_item)
{
	t_parser_stack_item	*item;

	item = raw_item;
	parser_cst_node_free(&item->cst_node);
}

void	parser_free(t_parser *parser)
{
	vector_free(&parser->stack, parser_free_stack_item);
	vector_free(&parser->tokens, parser_free_token);
	parser_cst_node_free(&parser->cst);
	free(parser->qualifiers);
	parser_init(parser);
}
