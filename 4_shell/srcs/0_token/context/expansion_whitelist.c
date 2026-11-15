/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_whitelist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:25:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:16:24 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

bool	is_in_context_param_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_in_context_backtick_whitelist(char c)
{
	return (c == '\\' || c == '$' || c == '`');
}

bool	is_in_context_backtick_special_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '"' || c == '\\');
}

bool	is_in_expansion_whitelist(char c, t_context context)
{
	if (context == CONTEXT_NONE)
		return (is_in_context_none_whitelist(c));
	else if (context == CONTEXT_PARAM)
		return (is_in_context_param_whitelist(c));
	else if (context == CONTEXT_BACKTICK)
		return (is_in_context_backtick_whitelist(c));
	else
		return (false);
}
