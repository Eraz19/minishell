/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   none.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:24:19 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/07 10:57:15 by adouieb          ###   ########.fr       */
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
