/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   none.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:53:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/07 10:58:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__quote_remove_context.h"

static t_context_args	context_none_rules(void)
{
	t_context_args	args;

	args.is_end = is_context_none_ending;
	args.is_in_whitelist = is_in_context_none_whitelist;
	return (args);
}

t_error	context_none(t_quote_remove *state)
{
	if (state->input[state->i] == '\0')
		return (state->reached_EOW = true, state->err);
	if (state->input[state->i] == '\\')
		return (context_escape(state, context_none_rules()));
	return (quote_remove_consume(state));
}
