/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:54:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 14:55:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "params.h"
#include "tilde_expansion_.h"

bool	is_tilde_expansion(t_expander *state, t_expander_word *word)
{
	t_expander_word_item	item;

	state->err = expander_word_peek(word, &item);
	if (state->err.type)
		return (false);
	return (item.c == '~');
}

t_error	tilde_expansion(
	t_expander *state,
	t_expander_word *word,
	t_expander_fields *fields)
{
	char	*path;
	t_buff	username;

	buff_init(&username, 0, NULL, 0);
	if ()
	state->err = params_get("HOME", &path);
	if (state->err.type)
		return (state->err);
	
	expander_word_get();
}