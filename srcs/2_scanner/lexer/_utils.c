/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:29:34 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 17:55:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_.h"

void	lexer_advance(t_lexer *state, size_t offset)
{
	state->input.i += offset;
}

t_error	lexer_consume(t_lexer *state, t_token_type type, size_t iter)
{
	size_t	i;
	char	current_char;

	i = 0;
	while (i < iter)
	{
		current_char = state->input.str[state->input.i];
		if (!buff_append(&state->token.value, &current_char, 1))
			return (state->err = ERR_LIBC, state->err);
		state->token.type = type;
		lexer_advance(state, 1);
		i++;
	}
	return (state->err);
}

t_lexer_backup	lexer_backup(t_lexer *state)
{
	t_lexer_backup res;

    res.i = state->input.i;
    res.context_len = state->input.context.len;
    res.token_value_len = state->token.value.len;
    res.token_type = state->token.type;
	return (res);
}

t_error	lexer_restore(t_lexer *state, t_lexer_backup backup)
{
	while (state->input.context.len > backup.context_len)
    {
		if (context_stack_pop(&state->input.context))
			return (state->err);
	}
    state->input.i = backup.i;
    state->token.type = backup.token_type;
    state->token.value.len = backup.token_value_len;
	return (state->err);
}

t_error	lexer_delimit_token(t_lexer *state, t_token *res)
{
    size_t	input_len;

    input_len = str_len(state->input.str);
	state->err = token_dup(res, &state->token);
	if (state->err)
		return (state->err);
	state->err = token_reset(&state->token, input_len);
	return (state->emited_token = true, state->err);
}
