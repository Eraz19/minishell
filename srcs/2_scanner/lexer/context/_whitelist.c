/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _whitelist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:55:46 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/29 12:24:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_context.h"

bool	is_in_ctx_backtick_special_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '"' || c == '\\');
}

bool	is_in_ctx_backtick_whitelist(char c)
{
    return (c == '\\' || c == '$' || c == '`');
}

bool	is_in_ctx_param_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_in_ctx_none_whitelist(char c)
{
	return ((void)c, true);
}
