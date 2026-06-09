/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   none.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:53:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:55:00 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__quote_remove_context.h"
#include "context.h"

static t_context_args	context_none_rules(void)
{
	t_context_args	args;

	args.is_end = is_context_none_ending;
	args.is_in_whitelist = is_in_context_none_whitelist;
	return (args);
}

t_error	expander_context_none(t_quote_remove *state)
{
	if (state->input[state->i] == '\0')
		return (state->reached_EOW = true, state->err);
	if (state->input[state->i] == '\\')
		return (expander_context_escape(state, context_none_rules()));
	return (quote_remove_consume(state));
}
