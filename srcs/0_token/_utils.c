/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:35:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 13:12:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_error	token_dup(t_token *dst, t_token *src)
{
	if (!buff_dup_n(&dst->value, &src->value, src->value.len))
		return (error_sys());
	return (dst->type = src->type, error(ERR_NO));
}
