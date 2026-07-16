#include <stdlib.h>
#include "lexer.h"
#include "cmd_sub.h"

t_error	lexer_context_cmd_sub(t_lexer *lexer)
{
	t_context_stack_item	*item;
	size_t					closing_par_index;

	if (lexer_consume(lexer, lexer->token->type, 2).type)
		return (lexer->err);
	lexer->err = context_stack_item_init(&item, CONTEXT_CMD_SUB);
	if (lexer->err.type)
		return (lexer->err);
	item->start = lexer->token->value.len;
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (free(item), lexer->err);
	lexer->err = cmd_sub_find_end(&closing_par_index);
	if (lexer->err.type)
		return (lexer->err);
	item->end = closing_par_index;
	if (lexer_consume(lexer, lexer->token->type, item->end - item->start).type)
		return (lexer->err);
	return (lexer->err);
}
