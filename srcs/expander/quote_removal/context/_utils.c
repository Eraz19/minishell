/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 16:28:32 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:46:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_remove_context_.h"

t_error	expander_context_escape(t_quote_remove *state, t_context_args args)
{
	if (state->input[state->i + 1] == '\0')
		return (state->reached_EOW = true, quote_remove_consume(state));
	if (!args.is_in_whitelist(state->input[state->i + 1]))
	{
		if (quote_remove_consume(state))
			return (state->err);
	}
	else
		quote_remove_advance(state, 1);
	return (quote_remove_consume(state));
}

t_error	expander_context_scan(t_quote_remove *state, t_context_args args)
{
	char	current_char;

	while (true)
	{
		if (state->err)
			return (state->err);
		current_char = state->input[state->i];
		if (current_char == '\0')
			return (state->reached_EOW = true, state->err);
		else if (args.is_end != NULL && args.is_end(current_char, NULL))
			return (quote_remove_advance(state, 1), state->err);
		else if (current_char == '\\' && args.is_in_whitelist != NULL)
			expander_context_escape(state, args);
		else
			quote_remove_consume(state);
	}
}
