/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_squote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:12:28 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 17:28:08 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

bool	is_context_dollar_squote_start(char *str)
{
	return (str[1] != '\0' && str[0] == '$' && str[1] == '\'');
}

bool	is_in_context_dollar_squote_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_context_dollar_squote_ending(char c, void *_)
{
	return (c == '\'');
}
