/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:14:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 21:26:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "reader_priv.h"

t_error	on_read_error(t_error err, const char *path)
{
	err = error_print(
			err,
			"scanner",
			path,
			"Unrecoverable read error",
			NULL, NULL);
	err.type = ERR_POSIX_READ;
	return (err);
}

t_error	on_open_error(t_error err, const char *path)
{
	if (err.type && err.type != ERR_LIBC)
		err = error_print(err, "scanner", path, NULL, NULL);
	if (err.type == ERR_FILE_NOT_FOUND)
		err.type = ERR_POSIX_CMD_NFOUND;
	else if (err.type == ERR_FILE_NOT_READABLE)
		err.type = ERR_POSIX_CMD_NEXC;
	if (err.type)
		env_set_last_status((int)err.type);
	return (err);
}
