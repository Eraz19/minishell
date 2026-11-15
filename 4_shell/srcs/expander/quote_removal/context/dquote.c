/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 18:36:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_dquote_rules(t_expander *expander)
{
	t_context_args	args;

	args.word = &expander->word;
	args.word_expanded = &expander->word_exp;
	args.is_end = is_context_dquote_ending;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (args);
}

t_error	context_dquote(t_expander *expander)
{
	return (context_scan(expander, context_dquote_rules(expander)));
}
