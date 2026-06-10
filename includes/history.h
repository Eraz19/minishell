/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:04:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:24:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "error.h"
# include "libft.h"
# include "history_rl_.h"
# include "history_list_.h"
# include "history_file_.h"

typedef struct s_history
{
	t_error			err;
	t_history_file	file;
	t_history_list	list;
	t_history_rl	rl_history;
	t_buff			current_input;
}	t_history;

void	history_init(t_history *state);
void	history_free(t_history *state);
t_error	history_load(t_history *state);

t_error	history_save(void);
t_error	history_save_entry(void);
t_error	history_append_to_entry(char *entry);

#endif
