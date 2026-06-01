/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:35:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 09:52:41 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_token.h"

t_error	token_dup(t_token *res, t_token *src)
{
	if (res == NULL || src == NULL)
		return (ERR_NULL_ARGS);
	if (!buff_dup_n(&res->value, &src->value, src->value.len))
		return (ERR_LIBC);
	res->type = src->type;
	return (ERR_NO);
}
