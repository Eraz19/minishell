#include <stdlib.h>
#include "lexer.h"

void	lexer_advance(t_lexer *lexer, size_t offset)
{
	lexer->input->i += offset;
}

t_error	lexer_consume(t_lexer *lexer, t_token_type type, size_t iter)
{
	size_t	i;
	char	current_char;

	i = 0;
	while (i < iter)
	{
		current_char = lexer->input->str.data[lexer->input->i];
		if (!string_append_n(&lexer->token->value, &current_char, 1))
			return (lexer->err = error_sys());
		lexer->token->type = type;
		lexer_advance(lexer, 1);
		i++;
	}
	return (lexer->err);
}

t_lexer_backup	lexer_backup(t_lexer *lexer)
{
	t_lexer_backup res;

    res.i = lexer->input->i;
    res.token_type = lexer->token->type;
    res.context_len = lexer->input->context.len;
    res.token_value_len = lexer->token->value.len;
    res.token_contexts_len = lexer->token->contexts.len;
	return (res);
}

t_error	lexer_restore(t_lexer *lexer, t_lexer_backup backup)
{
	t_context_stack_item	*item;

	while (lexer->input->context.len > backup.context_len)
	{
		lexer->err = context_stack_bpop(&lexer->input->context, NULL);
		if (lexer->err.type)
			return (lexer->err);
	}
	while (lexer->token->contexts.len > backup.token_contexts_len)
	{
		lexer->err = context_stack_bpop(&lexer->token->contexts, &item);
		if (lexer->err.type)
			return (lexer->err);
		free(item);
	}
    lexer->input->i = backup.i;
    lexer->token->type = backup.token_type;
    lexer->token->value.len = backup.token_value_len;
	return (lexer->err);
}

void	lexer_delimit_token(t_lexer *lexer)
{
	lexer->emited_token = true;
	if ()
	lexer->token->index.end = (ssize_t)lexer->input->i;
}
