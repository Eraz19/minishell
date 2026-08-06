/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_wait_and_reap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:50 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:09:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "posix_helpers.h"
#include "sig.h"
#include <errno.h>
#include <sys/wait.h>

// @ret ERR_NO / ERR_INTERRUPTED / ERR_LIBC
static inline t_error	process_wait_until_pending_trap(
							pid_t pid,
							int *process_status,
							int *wait_status)
{
	int		signo;
	t_error	err;

	while (true)
	{
		err = posix_wait(pid, process_status);
		if (err.type == ERR_LIBC && err.saved_errno == EINTR)
		{
			if (sig_has_pending_trap(&signo))
			{
				*wait_status = ERR_POSIX_SIGNAL_BASE_CODE + signo;
				err.type = ERR_INTERRUPTED;
				return (err);
			}
			continue ;
		}
		if (err.type == ERR_NO)
			*wait_status = *process_status;
		else
			*wait_status = (int)err.type;
		return (err);
	}
}

// @ret ERR_NO / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
static inline t_error	process_wait_target(
							t_process_table *table,
							size_t index,
							t_process *process,
							int *status)
{
	t_error	err;

	if (process->status < 0)
	{
		err = process_wait_until_pending_trap(
				process->pid, &process->status, status);
		if (err.type)
			return (err);
	}
	*status = process->status;
	if (!vector_remove(table, index, NULL))
		return (error(ERR_INTERNAL));
	return (error(ERR_NO));
}

// @ret ERR_NO / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
t_error	process_wait(t_process_table *table, pid_t pid, int *status)
{
	t_process	*process;
	size_t		i;

	i = 0;
	while (i < table->len)
	{
		process = &((t_process *)table->data)[i];
		if (process->pid == pid)
			return (process_wait_target(table, i, process, status));
		i++;
	}
	return (*status = 127, error(ERR_NO));
}

// @ret ERR_NO / ERR_INTERRUPTED / ERR_LIBC
t_error	process_wait_all(t_process_table *table, int *status)
{
	t_process	*process;
	size_t		i;
	t_error		wait_err;
	t_error		err;

	i = 0;
	err = error(ERR_NO);
	*status = 0;
	while (i < table->len)
	{
		process = &((t_process *)table->data)[i];
		if (process->status < 0)
		{
			wait_err = process_wait_until_pending_trap(
					process->pid, &process->status, status);
			if (wait_err.type == ERR_INTERRUPTED)
				return (wait_err);
			err = error_priorize(err, wait_err);
		}
		i++;
	}
	if (err.type)
		return (*status = (int)err.type, err);
	return (*status = 0, process_clear(table), err);
}

// @ret ERR_NO / ERR_LIBC
t_error	process_reap(t_process_table *table)
{
	t_process	*process;
	size_t		i;
	t_error		wait_err;
	t_error		err;

	i = 0;
	err = error(ERR_NO);
	while (i < table->len)
	{
		process = &((t_process *)table->data)[i];
		if (process->status < 0)
		{
			wait_err = posix_wait_with_opt(
					process->pid, WNOHANG, &process->status);
			if (wait_err.type == ERR_LIBC && wait_err.saved_errno == EINTR)
				return (error(ERR_NO));
			err = error_priorize(err, wait_err);
		}
		i++;
	}
	return (err);
}
