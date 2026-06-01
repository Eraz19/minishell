/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:21:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:37:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./quoting/_quote_remove.h"

t_error	expander_quote_remove(t_buff *res, t_buff *input)
{
	t_quote_remove	state;

	quote_remove_init(&state);
	quote_remove_load(&state, res, input);
	while (state.i < state.input->len)
	{
		if (state.err != ERR_NO)
			return (quote_remove_free(&state), state.err);
		if (state.input->data[state.i] == '\'') 
			quote_remove_ctx_squote(&state);
		else if (state.i + 1 < state.input->len &&
			state.input->data[state.i] == '$' &&
			state.input->data[state.i + 1] == '\'')
			quote_remove_ctx_dollar_squote(&state);
		else if (state.input->data[state.i] == '\"')
			quote_remove_ctx_dquote(&state);
		else
			quote_remove_ctx_none(&state);
	}
	return (quote_remove_free(&state), state.err);
}
