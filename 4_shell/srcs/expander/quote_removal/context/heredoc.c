/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:45:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "quote_removal_context_.h"

t_error	context_heredoc(t_expander *expander, t_word_item item)
{
	t_word_item	escaped;

	if (item.c != '\\' || expander->word.len == 0)
		return (expander->err = word_push(&expander->word_exp, item));
	expander->err = word_fpop(&escaped, &expander->word);
	if (expander->err.type)
		return (expander->err);
	if (!is_in_context_heredoc_whitelist(escaped.c))
	{
		expander->err = word_push(&expander->word_exp, item);
		if (expander->err.type)
			return (expander->err);
	}
	return (expander->err = word_push(&expander->word_exp, escaped));
}
