/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 19:03:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "debug.h"
#include "posix_helpers.h"
#include "history_file_priv.h"

t_error	write_history_file(t_history_file *history_file)
{
	int	fd;

	history_file_save_start_log(history_file);
	if (history_file->path.len == 0 || history_file->content.len == 0)
		return (history_file->err);
	history_file->err = open_history_file(
			&fd,
			history_file->path.data,
			O_CREAT | O_WRONLY | O_APPEND);
	if (history_file->err.type || fd < 0)
		return (history_file->err);
	history_file->err = posix_write(
			fd,
			history_file->content.data,
			history_file->content.len);
	history_file->err = error_priorize(
			history_file->err, posix_close_if_open(fd));
	if (history_file->err.type)
		on_history_file_write_error(history_file->err, history_file->path.data);
	history_file_save_end_log(history_file);
	return (history_file->err = error(ERR_NO));
}
