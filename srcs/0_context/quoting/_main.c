/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:22:38 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:27:44 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

bool	is_quoting_context(char *str, t_context *context)
{
	if (is_context_squote_start(str))
		return (*context = SQUOTE, true);
	else if (is_context_dollar_squote_start(str))
		return (*context = DOLLAR_SQUOTE, true);
	else if (is_context_dquote_start(str))
		return (*context = DQUOTE, true);
	return (false);
}

bool	is_in_quoting_whitelist(char c, t_context context)
{
	if (context == NONE_)
		return (is_in_context_none_whitelist(c));
	else if (context == SQUOTE)
		return (is_in_context_squote_whitelist(c));
	else if (context == DQUOTE)
		return (is_in_context_dquote_whitelist(c));
	else if (context == DOLLAR_SQUOTE)
		return (is_in_context_dollar_squote_whitelist(c));
	else
		return (false);
}

bool	is_quoting_ending(char c, t_context context)
{
	if (context == SQUOTE)
		return (is_context_squote_ending(c, NULL));
	else if (context == DQUOTE)
		return (is_context_dquote_ending(c, NULL));
	else if (context == DOLLAR_SQUOTE)
		return (is_context_dollar_squote_ending(c, NULL));
	else
		return (false);
}
