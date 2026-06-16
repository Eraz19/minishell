/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:34:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 12:59:10 by gastesan         ###   ########.fr       */
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
		return (error_sys());
	buff_init(&state->res, 0, NULL, 0);
	return (error(ERR_NO));
}
