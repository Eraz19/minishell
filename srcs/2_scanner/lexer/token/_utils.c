/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:35:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 19:37:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer_token.h"

t_error	token_dup(t_token *dst, t_token *src)
{
	if (!buff_dup_n(&dst->value, &src->value, src->value.len))
		return (ERR_LIBC);
	return (dst->type = src->type, ERR_NO);
}
