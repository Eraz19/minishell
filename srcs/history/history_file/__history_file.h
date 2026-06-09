/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __history_file.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:00:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 12:09:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HISTORY_FILE_H
# define __HISTORY_FILE_H

# include "error.h"
# include "libft.h"
# include "types.h"
# include "__history_list.h"

typedef struct s_history_file
{
	t_error			err;
	t_file_path		path;
	char			*content;
	t_history_list	loaded_list;
}	t_history_file;

void	history_file_init(t_history_file *state);
void	history_file_free(t_history_file *state);
t_error	history_file_load(t_history_file *state, t_file_path path, ssize_t max);
	
t_error	history_file_entry_serialize(char **entry);
void	history_file_entry_deserialize(char **entry);
t_error	history_file_open(t_history_file *state, int *fd, int flags);
t_error	history_file_extract_prev_entry(t_history_file *state, char **entry);

t_error	history_file_write(t_history_file *state, char *entry);
t_error	history_file_read(t_history_file *state, char **content);

#endif
