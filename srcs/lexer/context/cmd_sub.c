#include <stdlib.h>
#include "lexer.h"
#include "cmd_sub.h"
# include <stdio.h>

t_error	lexer_context_cmd_sub(t_lexer *lexer)
{
	t_context_stack_item	*item;
	ssize_t					closing_par_index;

	lexer->token->type = TOKEN_TOKEN;
	lexer->err = context_stack_item_init(&item, CONTEXT_CMD_SUB);
	if (lexer->err.type)
		return (lexer->err);
	item->start = lexer->token->value.len;
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (free(item), lexer->err);
	if (lexer_consume(lexer, lexer->token->type, 2).type)
		return (lexer->err);
	if (lexer->input->str.data[lexer->input->i + 1] == ')')
	{
		item->end = lexer->token->value.len;
		return (lexer_consume(lexer, lexer->token->type, 1));
	}
	lexer->err = cmd_sub_find_end(&closing_par_index, &lexer->token->ast_vector);
	if (lexer->err.type)
		return (lexer->err);
	if (closing_par_index < 0 || (size_t)closing_par_index < item->start)
		return (lexer->err = error(ERR_INCOHERENT_STATE));
	item->end = (size_t)closing_par_index - lexer->input->i + 2;
	fprintf(stderr, "%s(), end=%zu\n", __func__, item->end);
	return (lexer_consume(lexer, lexer->token->type, item->end - 1));
}
