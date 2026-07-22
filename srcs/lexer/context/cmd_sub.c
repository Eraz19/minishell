#include <stdlib.h>
#include "lexer.h"
#include "cmd_sub.h"

static t_error	cmd_sub_consume_body(t_lexer *lexer, t_context_stack_item *item)
{
	ssize_t		closing_par_index;

	lexer->err = cmd_sub_find_end(&closing_par_index,
			&lexer->token->ast_vector);
	if (lexer->err.type)
		return (lexer->err);
	if (closing_par_index < 0
		|| (size_t)closing_par_index < lexer->input->i)
		return (lexer->err = error(ERR_INCOHERENT_STATE));
	if (lexer_consume(lexer, lexer->token->type,
			(size_t)closing_par_index - lexer->input->i).type)
		return (lexer->err);
	item->end = lexer->token->value.len;
	return (lexer_consume(lexer, lexer->token->type, 1));
}

t_error	lexer_context_cmd_sub(t_lexer *lexer)
{
	t_context_stack_item	*item;

	lexer->token->type = TOKEN_TOKEN;
	lexer->err = context_stack_item_init(&item, CONTEXT_CMD_SUB);
	if (lexer->err.type)
		return (lexer->err);
	item->start = lexer->token->value.len;
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (free(item), lexer->err);
	// if (lexer_consume(lexer, lexer->token->type, 1).type)
	// 	return (lexer->err);
	// if (lexer->input->str.data[lexer->input->i] == '('
	// 	&& lexer->input->str.data[lexer->input->i + 1] == ')')
	// {
	// 	item->end = lexer->token->value.len;
	// 	return (lexer_consume(lexer, lexer->token->type, 2));
	// }
	return (cmd_sub_consume_body(lexer, item));
}
