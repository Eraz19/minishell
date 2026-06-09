/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 15:22:41 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:25:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "__history_rl.h"

void	history_rl_init(t_history_rl *state)
{
	state->count = 0;
}

void	history_rl_free(t_history_rl *state)
{
	rl_clear_history();
	state->count = 0;
}

void	history_rl_load(t_history_rl *state, ssize_t max)
{
	state->max = max;
}
