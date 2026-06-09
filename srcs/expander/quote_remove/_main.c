/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:21:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:00:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__quote_remove.h"
#include "__quote_remove_rules.h"

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
