/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   none.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:24:19 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:54:52 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

bool	is_in_context_none_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_context_none_ending(char c, void *_)
{
	return (c == '\0');
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}
