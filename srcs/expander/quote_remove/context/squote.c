/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:54:06 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/07 10:59:15 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__quote_remove_context.h"

static t_context_args	context_squote_rules(void)
{
	t_context_args	args;

	args.is_end = is_context_squote_ending;
	args.is_in_whitelist = NULL;
	return (args);
}

t_error	context_squote(t_quote_remove *state)
{
	quote_remove_advance(state, 1);
	return (context_scan(state, context_squote_rules()));
}
