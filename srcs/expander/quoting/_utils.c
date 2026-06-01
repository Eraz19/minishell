/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:58:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:37:24 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_quote_remove.h"

void	quote_remove_keep(t_quote_remove *state)
{
    if (!buff_append(state->expanded, &state->input->data[state->i], 1))
    {
        state->err = ERR_LIBC;
        return ;
    }
}

void	quote_remove_advance(t_quote_remove *state, size_t offset)
{
	state->i += offset;
}

void	quote_remove_consume(t_quote_remove *state)
{
	quote_remove_keep(state);
	quote_remove_advance(state, 1);
}
