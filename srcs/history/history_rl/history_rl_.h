/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_rl_.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 15:17:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:31:58 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_RL__H
# define HISTORY_RL__H

# include "error.h"
# include "history_list_.h"

typedef struct s_history_rl
{
	t_error	err;
	ssize_t	max;
	size_t	count;
}	t_history_rl;

void	history_rl_init(t_history_rl *state);
void	history_rl_free(t_history_rl *state);
t_error	history_rl_load(t_history_rl *state, t_history_list *list);

ssize_t	history_rl_to_add_count(t_history_rl *state, size_t count);

t_error	history_rl_add(t_history_rl *state, t_history_list *list, size_t count);

#endif
