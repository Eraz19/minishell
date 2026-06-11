/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file_.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:00:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:32:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_FILE__H
# define HISTORY_FILE__H

# include "error.h"
# include "types.h"
# include "history_list_.h"

typedef struct s_history_file
{
	t_error			err;
	t_file_path		path;
	char			*content;
	t_history_list	loaded_list;
}	t_history_file;

void	history_file_init(t_history_file *state);
void	history_file_free(t_history_file *state);
t_error	history_file_load(t_history_file *state, ssize_t max);
	
t_error	history_file_entry_serialize(char **entry);
void	history_file_entry_deserialize(char **entry);
t_error	history_file_open(t_history_file *state, int *fd, int flags);
t_error	history_file_extract_prev_entry(t_history_file *state, char **entry);

t_error	history_file_write(t_history_file *state, char *entry);
t_error	history_file_read(t_history_file *state, char **content);

#endif
