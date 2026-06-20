#include "parser_priv.h"
#include "token.h"

void	parser_init(t_parser *parser)
{
	parser_stack_init(&parser->stack);
	(void)vector_init(&parser->tokens, sizeof(t_token), 0);
	parser->lookahead_id = 0;
	parser->lookahead_symbol = SYM_NONE;
	parser->cst = NULL;
}

void	parser_free_token(void *token)
{
	token_free(token);
}

void	parser_free_stack_item(void *raw_item)
{
	t_stack_item	*item;

	item = raw_item;
	parser_cst_node_free(&item->cst_node);
}

void	parser_free(t_parser *parser)
{
	vector_free(&parser->stack, parser_free_stack_item);
	parser_cst_node_free(&parser->cst);
	vector_free(&parser->tokens, parser_free_token);
	parser_init(parser);
}
