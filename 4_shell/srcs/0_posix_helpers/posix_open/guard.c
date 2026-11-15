/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guard.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:43:22 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:30:12 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "posix_open_priv.h"
#include "error.h"
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdlib.h>

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

t_error	open_check_ub_args(int oflag, mode_t *optional_mode)
{
	if ((oflag & O_EXCL) && !(oflag & O_CREAT))
		return (open_invalid_args("POSIX: open(): invalid flag combination: "
				"O_EXCL without O_CREAT"));
	if ((oflag & O_TRUNC)
		&& !open_access_mode_is_write_or_rdwr(oflag))
		return (open_invalid_args("POSIX: open(): invalid flag combination: "
				"O_TRUNC without O_WRONLY or O_RDWR"));
	if ((oflag & O_CREAT) && optional_mode == NULL)
		return (open_invalid_args("POSIX: open(): missing mode: "
				"O_CREAT requires a mode argument"));
	return (error(ERR_NO));
}
