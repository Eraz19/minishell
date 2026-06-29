#include <stdlib.h>
#include "lexer.h"

void	lexer_advance(t_lexer *state, size_t offset)
{
	state->input->i += offset;
}

t_error	lexer_consume(t_lexer *state, t_token_type type, size_t iter)
{
	size_t	i;
	char	current_char;

	i = 0;
	while (i < iter)
	{
		current_char = state->input->str[state->input->i];
		if (!buff_append(&state->token->value, &current_char, 1))
			return (state->err = error_sys());
		state->token->type = type;
		lexer_advance(state, 1);
		i++;
	}
	return (state->err);
}

t_lexer_backup	lexer_backup(t_lexer *state)
{
	t_lexer_backup res;

    res.i = state->input->i;
    res.token_type = state->token->type;
    res.context_len = state->input->context.len;
    res.token_value_len = state->token->value.len;
    res.token_contexts_len = state->token->contexts.len;
	return (res);
}

t_error	lexer_restore(t_lexer *state, t_lexer_backup backup)
{
	t_context_parser_stack_item	*item;

	while (state->input->context.len > backup.context_len)
    {
		if (context_stack_bpop(&state->input->context, NULL).type)
			return (state->err);
	}
	while (state->token->contexts.len > backup.token_contexts_len)
	{
		if (context_stack_bpop(&state->token->contexts, &item).type)
			return (state->err);
		free(item);
	}
    state->input->i = backup.i;
    state->token->type = backup.token_type;
    state->token->value.len = backup.token_value_len;
	return (state->err);
}

void	lexer_delimit_token(t_lexer *state)
{
	state->emited_token = true;
	state->token->index.end = (ssize_t)state->input->i;
}
