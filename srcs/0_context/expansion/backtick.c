/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:12:44 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 17:35:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

bool	is_context_backtick_start(char *str)
{
	return (str[0] == '`');
}

bool	is_in_context_backtick_special_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '"' || c == '\\');
}

bool	is_in_context_backtick_whitelist(char c)
{
    return (c == '\\' || c == '$' || c == '`');
}

bool	is_context_backtick_ending(char c, void *_)
{
	return (c == '`');
}
