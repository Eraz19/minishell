/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posix_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:43:38 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:43:39 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <errno.h>
#include <stdbool.h>
#include <sys/wait.h>

// @ret ERR_NO / ERR_LIBC
static inline t_error	posix_wait_priv(
							pid_t pid,
							int options,
							int *status,
							bool retry)
{
	pid_t	ret;

	*status = -1;
	while (true)
	{
		ret = waitpid(pid, status, options);
		if (ret == 0)
			return (error(ERR_NO));
		else if (ret > 0)
			break ;
		else if (retry && errno == EINTR)
			continue ;
		return (error_sys());
	}
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = ERR_POSIX_SIGNAL_BASE_CODE + WTERMSIG(*status);
	return (error(ERR_NO));
}

t_error	posix_wait(pid_t pid, int *exit_status)
{
	return (posix_wait_priv(pid, 0, exit_status, false));
}

t_error	posix_wait_with_opt(pid_t pid, int options, int *exit_status)
{
	return (posix_wait_priv(pid, options, exit_status, false));
}

t_error	posix_wait_and_retry(pid_t pid, int *exit_status)
{
	return (posix_wait_priv(pid, 0, exit_status, true));
}

t_error	posix_wait_with_opt_and_retry(pid_t pid, int options, int *exit_status)
{
	return (posix_wait_priv(pid, options, exit_status, true));
}
