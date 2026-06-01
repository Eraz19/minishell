/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ending.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:00:25 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/29 18:18:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_context.h"

bool	is_ctx_backtick_ending(char c)
{
	return (c == '`');
}

bool	is_ctx_dollar_squote_ending(char c)
{
	return (c == '\'');
}

bool	is_ctx_dquote_ending(char c)
{
	return (c == '\"');
}

bool	is_ctx_param_ending(char c)
{
	return (c == '}');
}

bool	is_ctx_squote_ending(char c)
{
	return (c == '\'');
}
