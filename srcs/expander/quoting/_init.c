/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:34:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:37:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "./_quote_remove.h"

void	quote_remove_init(t_quote_remove *state)
{
	if (state == NULL)
		return ;
	*state = (t_quote_remove){0};
	buff_init(state->input, 0, NULL, 0);
	buff_init(state->expanded, 0, NULL, 0);
}

void	quote_remove_free(t_quote_remove *state)
{
	if (state == NULL)
		return ;
	*state = (t_quote_remove){0};
}

t_error	quote_remove_load(t_quote_remove *state, t_buff *res, t_buff *input)
{
	if (state == NULL || res == NULL || input == NULL)
		return (ERR_NULL_ARGS);
	state->input = input;
	state->expanded = res;
	return (ERR_NO);
}
