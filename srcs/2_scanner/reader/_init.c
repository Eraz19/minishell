/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:36:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/29 15:13:14 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_reader.h"

void	reader_init(t_reader *state)
{
	if (state == NULL)
		return ;
	*state = (t_reader){0};
}

void	reader_free(t_reader *state)
{
	if (state == NULL)
		return ;
	*state = (t_reader){0};
}

void	reader_load(t_reader *state, t_scanner_ctx_stack *ctx)
{
	if (state == NULL)
		return ;
	state->ctx = ctx;
}
