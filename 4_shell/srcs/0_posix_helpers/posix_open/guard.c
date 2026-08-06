/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guard.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:43:22 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:46:17 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "posix_open_priv.h"
#include "error.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>

static inline t_error	open_invalid_args(const char *message)
{
	(void)undefined_behaviour(message);
	return (error_print(
			error(ERR_INVALID_USAGE),
			message,
			NULL,
			NULL));
}

static inline bool	open_access_mode_is_write_or_rdwr(int oflag)
{
	int	access_mode;

	access_mode = oflag & O_ACCMODE;
	return (access_mode == O_WRONLY || access_mode == O_RDWR);
}

/*
** POSIX allows O_EXEC and O_SEARCH to have implementation-specific values,
** and access modes are not guaranteed to be distinct bit flags.
** Avoid treating aliases of O_RDONLY/O_WRONLY/O_RDWR as invalid.
*/
static inline bool	open_access_mode_is_exec_or_search(int oflag)
{
#if defined(O_EXEC) || defined(O_SEARCH)
	int	access_mode;

	access_mode = oflag & O_ACCMODE;
#endif
#ifdef O_EXEC
	if (O_EXEC != O_RDONLY
		&& O_EXEC != O_WRONLY
		&& O_EXEC != O_RDWR
		&& access_mode == O_EXEC)
		return (true);
#endif
#ifdef O_SEARCH
	if (O_SEARCH != O_RDONLY
		&& O_SEARCH != O_WRONLY
		&& O_SEARCH != O_RDWR
		&& access_mode == O_SEARCH)
		return (true);
#endif
	(void)oflag;
	return (false);
}

static inline bool	open_mode_has_only_permission_bits(mode_t mode)
{
	mode_t	permission_bits;

	permission_bits = S_IRWXU | S_IRWXG | S_IRWXO;
	return ((mode & ~permission_bits) == 0);
}

t_error	open_check_ub_args(int oflag, mode_t *optional_mode)
{
	if ((oflag & O_EXCL) && !(oflag & O_CREAT))
		return (open_invalid_args("POSIX: open(): invalid flag combination: "
				"O_EXCL without O_CREAT"));
	if ((oflag & O_TRUNC) && !open_access_mode_is_write_or_rdwr(oflag))
		return (open_invalid_args("POSIX: open(): invalid flag combination: "
				"O_TRUNC without O_WRONLY or O_RDWR"));
	if ((oflag & O_CREAT) && optional_mode == NULL)
		return (open_invalid_args("POSIX: open(): missing mode: "
				"O_CREAT requires a mode argument"));
	if ((oflag & O_CREAT)
		&& optional_mode != NULL
		&& !open_mode_has_only_permission_bits(*optional_mode))
		return (open_invalid_args("POSIX: open(): invalid mode: "
				"O_CREAT mode contains bits other than file permission bits"));
#ifdef O_DIRECTORY
	if ((oflag & O_CREAT)
		&& (oflag & O_DIRECTORY)
		&& !open_access_mode_is_write_or_rdwr(oflag))
		return (open_invalid_args("POSIX: open(): invalid flag combination: "
				"O_CREAT with O_DIRECTORY without O_WRONLY or O_RDWR"));
#endif
	if ((oflag & O_CREAT) && open_access_mode_is_exec_or_search(oflag))
		return (open_invalid_args("POSIX: open(): invalid flag combination: "
				"O_CREAT with O_EXEC or O_SEARCH"));
	return (error(ERR_NO));
}
