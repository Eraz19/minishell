/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:46:02 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 18:40:49 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_squote_rules(t_expander *expander)
{
	t_context_args	args;

	args.word = &expander->word;
	args.is_in_whitelist = NULL;
	args.word_expanded = &expander->word_exp;
	args.is_end = is_context_squote_ending;
	return (args);
}

t_error	context_squote(t_expander *expander)
{
	return (context_scan(expander, context_squote_rules(expander)));
}
