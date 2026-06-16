/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:21:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 23:47:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_removal_.h"
#include "quote_remove_rules_.h"

t_error	quote_removal(t_expansion *expansion)
{
	t_buff	expanded_word;

	if (!buff_init(&expanded_word, 0, state->word, (long)str_len(state->word)))
		return (ERR_LIBC);
	while (!state.reached_EOW)
	{
		if (quote_remove_rules(&state))
			return (quote_remove_free(&state));
	}
	if (!buff_dup_n(res, &state.res, state.res.len))
		state.err = ERR_LIBC;
	return (quote_remove_free(&state));
}
