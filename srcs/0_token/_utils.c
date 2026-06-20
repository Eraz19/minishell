/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:35:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 15:59:00 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_error	token_dup(t_token *dst, t_token *src)
{
	dst->type = src->type;
	if (!buff_dup_n(&dst->value, &src->value, src->value.len))
		return (error_sys());
	return (context_stack_dup(&dst->contexts, &src->contexts));
}
