/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __history_rl.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 15:17:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 12:07:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HISTORY_RL_H
# define __HISTORY_RL_H

# include "error.h"
# include "libft.h"
# include "__history_list.h"

typedef struct s_history_rl
{
	t_error	err;
	ssize_t	max;
	size_t	count;
}	t_history_rl;

void	history_rl_init(t_history_rl *state);
void	history_rl_free(t_history_rl *state);
void	history_rl_load(t_history_rl *state, ssize_t max);

ssize_t	history_rl_to_add_count(t_history_rl *state, size_t count);

t_error	history_rl_add(t_history_rl *state, t_history_list *list, size_t count);

#endif
