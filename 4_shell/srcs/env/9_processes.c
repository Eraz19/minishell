/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_processes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:15:05 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:15:06 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "shell.h"
#include "process.h"

// @ret ERR_INTERNAL
static inline t_error	env_get_state(t_params **dst)
{
	*dst = shell_get_params();
	if (dst != NULL)
		return (error(ERR_NO));
	(void)error_print(error(ERR_SHELL_NOT_FOUND),
		"params", __func__, NULL, NULL);
	return (error(ERR_INTERNAL));
}

t_error	env_register_process(pid_t pid)
{
	t_params	*params;
	t_error		err;

	err = env_get_state(&params);
	if (err.type)
		return (err);
	specials_set_last_bg_pid(&params->specials, pid);
	specials_set_last_status(&params->specials, 0);
	return (process_register(&params->processes, pid));
}

t_error	env_wait(pid_t pid, int *status)
{
	t_params	*params;
	t_error		err;

	err = env_get_state(&params);
	if (err.type)
		return (err);
	return (process_wait(&params->processes, pid, status));
}

t_error	env_wait_all(int *status)
{
	t_params	*params;
	t_error		err;

	err = env_get_state(&params);
	if (err.type)
		return (err);
	return (process_wait_all(&params->processes, status));
}

t_error	env_reap(void)
{
	t_params	*params;
	t_error		err;

	err = env_get_state(&params);
	if (err.type)
		return (err);
	return (process_reap(&params->processes));
}
