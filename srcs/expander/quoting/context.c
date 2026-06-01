/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:20:51 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:37:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"
#include "_quote_remove.h"

void	quote_remove_ctx_squote(t_quote_remove *state)
{
	quote_remove_advance(state, 1);
	state->ctx = SQUOTE;
	state->is_escaping = false;
	while (state->i < state->input->len)
	{
		if (state->err || !quote_remove(state))
			return ;
	}
}

void	quote_remove_ctx_dquote(t_quote_remove *state)
{
	quote_remove_advance(state, 1);
	state->ctx = DQUOTE;
	state->is_escaping = true;
	while (state->i < state->input->len)
	{
		if (state->err || !quote_remove(state))
			return ;
	}
}

void	quote_remove_ctx_dollar_squote(t_quote_remove *state)
{
	quote_remove_advance(state, 2);
	state->is_escaping = true;
	state->ctx = DOLLAR_SQUOTE;
	while (state->i < state->input->len)
	{
		if (state->err || !quote_remove(state))
			return ;
	}
}

void	quote_remove_ctx_none(t_quote_remove *state)
{
	state->ctx = NONE_;
	state->is_escaping = true;
	quote_remove(state), true;
}
