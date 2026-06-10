/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_squote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:53:21 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:46:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "quote_remove_context_.h"

static t_context_args	context_dollar_squote_rules(void)
{
	t_context_args	args;

	args.is_end = is_context_dollar_squote_ending;
	args.is_in_whitelist = is_in_context_dollar_squote_whitelist;
	return (args);
}

t_error	expander_context_dollar_squote(t_quote_remove *state)
{	
	quote_remove_advance(state, 2);
	return (expander_context_scan(state, context_dollar_squote_rules()));
}
