/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:58:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/06 16:39:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__quote_remove.h"

t_error	quote_remove_keep(t_quote_remove *state)
{
	if (!buff_append(&state->res, state->input + state->i, 1))
		state->err = ERR_LIBC;
	return (state->err);
}

void	quote_remove_advance(t_quote_remove *state, size_t offset)
{
	state->i += offset;
}

t_error	quote_remove_consume(t_quote_remove *state)
{
	if (quote_remove_keep(state))
		return (state->err);
	return (quote_remove_advance(state, 1), state->err);
}
