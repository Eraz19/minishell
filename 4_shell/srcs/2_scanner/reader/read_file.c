/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:14:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:54:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h> // IWYU pragma: keep
#include <sys/stat.h>
#include "reader_priv.h"
#include "posix_helpers.h"
#include "utils.h"

t_error	fd_is_readable_file(int fd)
{
	struct stat	infos;

	if (fstat(fd, &infos) != 0)
		return (error_sys());
	if (S_ISDIR(infos.st_mode))
		return (error(ERR_FILE_NOT_READABLE));
	return (error(ERR_NO));
}

t_error	open_file(const char *path, int *fd)
{
	t_error	err;
	bool	ref_found;

	err = file_check(path, READABLE, &ref_found);
	if (err.type == ERR_NO)
	{
		err = posix_open(path, O_RDONLY, fd);
		if (err.saved_errno == ENOENT || err.saved_errno == ENOTDIR)
			err.type = ERR_FILE_NOT_FOUND;
		else if (err.type)
			err.type = ERR_FILE_NOT_READABLE;
	}
	if (err.type == ERR_NO)
	{
		err = fd_is_readable_file(*fd);
		if (err.type)
		{
			(void)posix_close_if_open(*fd);
			err.type = ERR_FILE_NOT_READABLE;
		}
	}
	return (on_open_error(err, path));
}

t_error	read_file(t_string *out, const char *path)
{
	int		fd;
	t_error	err;

	err = open_file(path, &fd);
	if (err.type)
		return (err);
	err = posix_read_all(fd, out);
	if (err.type)
	{
		err = error_priorize(on_read_error(err, path), posix_close_if_open(fd));
		return (err);
	}
	(void)posix_close_if_open(fd);
	return (err);
}
