/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:34:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 23:45:09 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "quote_removal_.h"

void	quote_remove_init(t_quote_remove *state)
{
	*state = (t_quote_remove){0};
	buff_init(&state->expanded_word, 0, NULL, 0);
}

t_error	quote_remove_free(t_quote_remove *state)
{
	if (state->word)
		free(state->word);
	buff_free(&state->expanded_word);
	return (*state = (t_quote_remove){0}, err);
}

t_error	quote_remove_load(t_quote_remove *state, t_buff *word)
{
	state->word = buff_get_string(word);
	if (state->word == NULL)
		return (state->err = ERR_LIBC);
	return (state->err);
}
