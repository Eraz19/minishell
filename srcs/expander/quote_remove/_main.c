/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:21:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:45:31 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_remove_.h"
#include "quote_remove_rules_.h"

t_error	quote_remove(t_buff *res, t_buff *input)
{
	t_quote_remove	state;

	quote_remove_init(&state);
	state.err = quote_remove_load(&state, input);
	if (state.err)
		return (quote_remove_free(&state));
	while (!state.reached_EOW)
	{
		if (quote_remove_rules(&state))
			return (quote_remove_free(&state));
	}
	if (!buff_dup_n(res, &state.res, state.res.len))
		state.err = ERR_LIBC;
	return (quote_remove_free(&state));
}
