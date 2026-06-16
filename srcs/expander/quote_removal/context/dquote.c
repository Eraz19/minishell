/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:53:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:46:49 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "quote_remove_context_.h"

static t_context_args	context_dquote_rules(void)
{
	t_context_args	args;

	args.is_end = is_context_dquote_ending;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (args);
}

t_error	expander_context_dquote(t_quote_remove *state)
{
	quote_remove_advance(state, 1);
	return (expander_context_scan(state, context_dquote_rules()));
}
