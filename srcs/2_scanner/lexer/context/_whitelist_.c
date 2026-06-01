/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _whitelist_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:59:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/29 12:24:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_context.h"

bool	is_in_ctx_dollar_squote_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_in_ctx_dquote_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '\\' || c == '\"');
}

bool	is_in_ctx_squote_whitelist(char c)
{
	return ((void)c, false);
}
