/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:53:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 15:46:21 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_dquote_rules(
	t_expander_word *word,
	t_expander_word *word_expanded)
{
	t_context_args	args;
	
	args.word = word;
	args.context = DQUOTE;
	args.word_expanded = word_expanded;
	args.is_end = is_context_dquote_ending;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (args);
}

t_error	context_dquote(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	return (context_scan(state, context_dquote_rules(word, word_exp)));
}
