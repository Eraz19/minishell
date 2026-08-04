/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_recognition.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:10:48 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:10:49 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

bool	is_context_quoting(t_context context)
{
	return (context == CONTEXT_SQUOTE
		|| context == CONTEXT_DQUOTE
		|| context == CONTEXT_DOLLAR_SQUOTE);
}
