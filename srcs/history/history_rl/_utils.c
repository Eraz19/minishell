/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 11:23:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:33:58 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_rl_.h"

ssize_t	history_rl_to_add_count(t_history_rl *state, size_t count)
{
	if (state->max < 0)
		return ((ssize_t)count);
	else if (state->count + count > (size_t)(state->max))
		return (-(ssize_t)state->max);
	else
		return ((ssize_t)count);
}
