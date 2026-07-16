#include <stdlib.h>
#include "lexer.h"
#include "cmd_sub.h"

t_error	run_cmd_sub_detection(t_lexer *lexer, t_token *cmd_sub_token)
{
	t_string	input;
	size_t		closing_par_index;

	token_init(cmd_sub_token);
	if (lexer->input == NULL)
		return (token_free(cmd_sub_token), error(ERR_NO_INPUT_TO_LEX));
	if (!string_init(&input, 0, lexer->input->str.data + lexer->input->i, -1))
	{
		lexer->err = error_sys();
		return (token_free(cmd_sub_token), lexer->err);
	}
	lexer->err = cmd_sub_find_end(&closing_par_index);
	return (token_free(cmd_sub_token), string_free(&input), lexer->err);
}

t_error	update_context_cmd_sub(
	t_lexer *lexer,
	t_token *cmd_sub_token,
	t_context_stack_item *item)
{
	item->end = (size_t)cmd_sub_token->index.end;
	if (lexer_consume(lexer, lexer->token->type, item->end - item->start).type)
		return (lexer->err);
	return (lexer->err);
}

t_error	lexer_context_cmd_sub(t_lexer *lexer)
{
	t_context_stack_item	*item;
	t_token					cmd_sub_token;

	if (lexer_consume(lexer, lexer->token->type, 2).type)
		return (lexer->err);
	lexer->err = context_stack_item_init(&item, CONTEXT_CMD_SUB);
	if (lexer->err.type)
		return (lexer->err);
	item->start = lexer->token->value.len;
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (free(item), lexer->err);
	while (true)
	{
		if(run_cmd_sub_detection(lexer, &cmd_sub_token).type)
			return (lexer->err);
		if (cmd_sub_token.index.end == -1 && context_EOI(lexer).type)
			return (lexer->err);
		if (cmd_sub_token.index.end != -1)
			return (update_context_cmd_sub(lexer, &cmd_sub_token, item));
	}
}
