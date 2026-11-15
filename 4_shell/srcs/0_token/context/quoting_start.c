/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:10:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:10:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

bool	is_context_squote_start(char *str)
{
	return (str[0] == '\'');
}

bool	is_context_dquote_start(char *str)
{
	return (str[0] == '\"');
}

bool	is_context_dollar_squote_start(char *str)
{
	return (str[0] == '$' && str[1] == '\'');
}

bool	is_quoting_context_start(char *str, t_context *context)
{
	if (is_context_squote_start(str))
		return (*context = CONTEXT_SQUOTE, true);
	else if (is_context_dollar_squote_start(str))
		return (*context = CONTEXT_DOLLAR_SQUOTE, true);
	else if (is_context_dquote_start(str))
		return (*context = CONTEXT_DQUOTE, true);
	return (false);
}
