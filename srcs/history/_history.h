/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _history.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:06:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 13:35:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HISTORY_H
# define _HISTORY_H

# include "libft.h"
# include "history_list/_history_list.h"

typedef struct s_history
{
	t_error			err;
	const char 		*path;
	t_history_list	entries;
	ssize_t			max_entries;
	t_buff			current_input;
	size_t			loaded_entries;
	size_t			entries_in_rlhistory;
}	t_history;

void		history_rl_history_free(t_history *state);
t_error		history_rl_add_entries(t_history *state, size_t count);

t_error		history_add_squote_escaping(char **entry);
void		history_remove_squote_escaping(char **entry);
char		*history_find_last_unescaped_squote(char *entry);

t_error		history_read_file(char **content, t_history *state);
t_error		history_write_in_file(t_history *state, char *entry);

t_history	*shell_get_history(void);

#endif
