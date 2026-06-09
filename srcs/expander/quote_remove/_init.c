/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:34:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/07 11:19:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "__quote_remove.h"

void	quote_remove_init(t_quote_remove *state)
{
	*state = (t_quote_remove){0};
}

t_error	quote_remove_free(t_quote_remove *state)
{
	t_error	err;

	err = state->err;
	if (state->input)
		free(state->input);
	buff_free(&state->res);
	return (*state = (t_quote_remove){0}, err);
}

t_error	quote_remove_load(t_quote_remove *state, t_buff *input)
{
	state->input = buff_get_string(input);
	if (state->input == NULL)
		return (ERR_LIBC);
	buff_init(&state->res, 0, NULL, 0);
	return (ERR_NO);
}
