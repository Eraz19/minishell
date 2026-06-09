/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:40:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:21:15 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer_rules.h"
#include "__lexer_context.h"

static t_error	context_top_level_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_none_whitelist;
	return (context_escape(state, args));
}

bool	is_in_middle_of_word(t_lexer *state)
{
	return (state->token.type == TOKEN);
}

t_error	lexer_rule_in_middle_of_word(t_lexer *state)  // Rule 8
{
	if (state->input[state->i] == '\\')
		return (context_top_level_escape(state));
	else
		return (lexer_consume(state, TOKEN, 1));
}

t_error	lexer_rule_new_word(t_lexer *state) // Rule 10
{
	if (state->input[state->i] == '\\')
		return (context_top_level_escape(state));
	else
		return (lexer_consume(state, TOKEN, 1));
}
