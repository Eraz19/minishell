/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_walk_pipe_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:09 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:23:10 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "walk_pipeline_priv.h"
#include "posix_helpers.h"
#include <unistd.h>

t_error	walk_pipe_close_fd(t_pipe_run *run, int fd)
{
	t_error	err;

	if (fd == -1)
		return (error(ERR_NO));
	err = posix_close_if_open(fd);
	if (run->pipe_fds[READ_ID] == fd)
		run->pipe_fds[READ_ID] = -1;
	if (run->pipe_fds[WRITE_ID] == fd)
		run->pipe_fds[WRITE_ID] = -1;
	if (run->cmd_fds[READ_ID] == fd)
		run->cmd_fds[READ_ID] = -1;
	if (run->cmd_fds[WRITE_ID] == fd)
		run->cmd_fds[WRITE_ID] = -1;
	return (err);
}

t_error	walk_pipe_close_all_fds(t_pipe_run *run)
{
	t_error	err;

	err = walk_pipe_close_fd(run, run->pipe_fds[READ_ID]);
	if (err.type == ERR_NO)
		err = walk_pipe_close_fd(run, run->pipe_fds[WRITE_ID]);
	if (err.type == ERR_NO)
		err = walk_pipe_close_fd(run, run->cmd_fds[READ_ID]);
	if (err.type == ERR_NO)
		err = walk_pipe_close_fd(run, run->cmd_fds[WRITE_ID]);
	return (err);
}

static inline t_error	walk_pipe_close_tmp(int tmp[3], size_t len)
{
	size_t	i;
	t_error	err;
	t_error	tmp_err;

	i = 0;
	err = error(ERR_NO);
	while (i < len)
	{
		tmp_err = posix_close_if_open(tmp[i]);
		err = error_priorize(err, tmp_err);
		i++;
	}
	return (err);
}

static inline t_error	walk_pipe_move_above_std(t_pipe_run *run, int *fd)
{
	int		tmp[3];
	size_t	len;
	int		new_fd;
	t_error	err;
	t_error	err_cleanup;

	if (*fd < 0 || *fd > STDERR_FILENO)
		return (error(ERR_NO));
	len = 0;
	new_fd = dup(*fd);
	while (new_fd >= 0 && new_fd <= STDERR_FILENO)
	{
		tmp[len++] = new_fd;
		new_fd = dup(*fd);
	}
	if (new_fd < 0)
		return (err = error_sys(), walk_pipe_close_tmp(tmp, len), err);
	err = walk_pipe_close_fd(run, *fd);
	*fd = new_fd;
	err_cleanup = walk_pipe_close_tmp(tmp, len);
	return (error_priorize(err, err_cleanup));
}

t_error	walk_pipe_next_pipe(t_pipe_run *run)
{
	bool	is_first;
	bool	is_last;
	t_error	err;

	is_first = run->command_id == 0;
	is_last = run->command_id == run->pipeline->commands.len - 1;
	if (is_first == true)
		run->cmd_fds[READ_ID] = -1;
	else
		run->cmd_fds[READ_ID] = run->pipe_fds[READ_ID];
	if (is_last == true)
	{
		run->cmd_fds[WRITE_ID] = -1;
		return (error(ERR_NO));
	}
	if (pipe(run->pipe_fds) == -1)
		return (error_sys());
	err = walk_pipe_move_above_std(run, &run->pipe_fds[READ_ID]);
	if (err.type == ERR_NO)
		err = walk_pipe_move_above_std(run, &run->pipe_fds[WRITE_ID]);
	if (err.type)
		return (err);
	run->cmd_fds[WRITE_ID] = run->pipe_fds[WRITE_ID];
	return (err);
}
