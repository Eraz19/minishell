/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:29:49 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 15:19:13 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "expander.h"
#include "quote_removal_.h"

t_error	expander_word(
	t_expansion *expansion,
	t_token token,
	t_expander_mode mode)
{
	t_error		err;

	expander_init(expansion);
	err = expander_load(expansion, word);
	if (err)
		return (err);
	if (mode == QUOTE_REMOVE_ONLY)
		return (quote_removal(expansion));
	else
	{
		
	}
}
