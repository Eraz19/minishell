/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:40:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:23:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_token.h"
#include "../context/_context.h"

static bool	ctx_top_level_escape(t_lexer *state)
{
	t_escape_handler	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.is_in_whitelist = is_in_ctx_none_whitelist;
	args.enable_line_continuation = true;
	return (ctx_escape(state, args));
}

bool	lexer_in_middle_of_word(t_lexer *state)  // Rule 8
{
	if (state->token.type == TOKEN)
	{
		if (state->input[state->i] == '\\')
			return (ctx_top_level_escape(state));
		else
			return (lexer_consume(state, TOKEN, 1), true);
	}
	return (false);
}

void	lexer_new_word(t_lexer *state) // Rule 10
{
	if (state->input[state->i] == '\\')
		ctx_top_level_escape(state);
	else
		lexer_consume(state, TOKEN, 1);
}
