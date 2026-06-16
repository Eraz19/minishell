/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:29:49 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 23:47:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "quote_removal_.h"

t_error	expander_word(t_expansion *expansion, char *word, t_expander_mode mode)
{
	t_error		err;

	expander_init(expansion);
	err = expander_load(expansion, word);
	if (err)
		return (err);
	if (mode == QUOTE_REMOVE_ONLY)
		return (quote_removal(expansion, expansion));
	else
	{
		
	}
}
