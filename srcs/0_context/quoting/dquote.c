/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:12:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 17:29:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

bool	is_context_dquote_start(char *str)
{
	return (str[0] == '\"');
}

bool	is_in_context_dquote_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '\\' || c == '\"');
}

bool	is_context_dquote_ending(char c, void *_)
{
	return (c == '\"');
}
