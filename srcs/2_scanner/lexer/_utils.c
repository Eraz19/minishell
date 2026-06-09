/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:29:34 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 19:38:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer.h"

void	lexer_advance(t_lexer *state, size_t offset)
{
	state->i += offset;
}

t_error	lexer_consume(t_lexer *state, t_token_type type, size_t iter)
{
	size_t	i;

	i = 0;
	while (i < iter)
	{
		if (!buff_append(&state->token.value, &state->input[state->i], 1))
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

    res.i = state->i;
    res.context_len = state->context.len;
    res.token_value_len = state->token.value.len;
    res.token_type = state->token.type;
	return (res);
}

t_error	lexer_restore(t_lexer *state, t_lexer_backup backup)
{
	while (state->context.len > backup.context_len)
    {
		if (context_stack_pop(&state->context))
			return (state->err);
	}
    state->i = backup.i;
    state->token.type = backup.token_type;
    state->token.value.len = backup.token_value_len;
	return (state->err);
}

t_error	lexer_delimit_token(t_lexer *state, t_token *res)
{
    size_t	input_len;

    input_len = str_len(state->input);
	state->err = token_dup(res, &state->token);
	if (state->err)
		return (state->err);
	state->err = token_reset(&state->token, input_len);
	return (state->emited_token = true, state->err);
}
