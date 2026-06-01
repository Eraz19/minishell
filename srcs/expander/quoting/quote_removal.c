/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:17:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:37:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_quote_remove.h"

bool	quote_remove(t_quote_remove *state)
{
	char	next_char;

	if (state->input->data[state->i] == '\\')
	{
		if (state->i + 1 >= state->input->len)
			return (quote_remove_consume(state), true);
		else
		{
			next_char = state->input->data[state->i + 1];
			if (!scanner_is_in_quoting_whitelist(next_char, state->ctx))
				quote_remove_keep(state);
			if (state->err)
				return (true);
			quote_remove_advance(state, 1);
			if (state->is_escaping)
				return (quote_remove_consume(state), true);
		}
	}
	else
	{
		if (scanner_is_quoting_ending(state->input->data[state->i], state->ctx))
			return (quote_remove_advance(state, 1), false);
		return (quote_remove_consume(state), true);
	}
	return (true);
}
