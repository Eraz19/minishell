/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_whitelist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:10:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:10:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

bool	is_in_context_squote_whitelist(char c)
{
	return ((void)c, false);
}

bool	is_in_context_dquote_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '\\' || c == '\"');
}

bool	is_in_context_dollar_squote_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_in_quoting_whitelist(char c, t_context context)
{
	if (context == CONTEXT_NONE)
		return (is_in_context_none_whitelist(c));
	else if (context == CONTEXT_SQUOTE)
		return (is_in_context_squote_whitelist(c));
	else if (context == CONTEXT_DQUOTE)
		return (is_in_context_dquote_whitelist(c));
	else if (context == CONTEXT_DOLLAR_SQUOTE)
		return (is_in_context_dollar_squote_whitelist(c));
	else if (context == CONTEXT_HEREDOC)
		return (is_in_context_heredoc_whitelist(c));
	else
		return (false);
}
