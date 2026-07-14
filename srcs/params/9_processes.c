#include "params.h"
#include "shell.h"
#include "process.h"

// @ret ERR_INTERNAL
static inline t_error	params_get_state(t_params **dst)
{
	*dst = shell_get_params();
	if (dst != NULL)
		return (error(ERR_NO));
	(void)error_print(error(ERR_SHELL_NOT_FOUND),
		"params", __func__, NULL, NULL);
	return (error(ERR_INTERNAL));
}

t_error	params_register_process(pid_t pid)
{
	t_params	*params;
	t_error		err;

	err = params_get_state(&params);
	if (err.type)
		return (err);
	specials_set_last_bg_pid(&params->specials, pid);
	specials_set_last_status(&params->specials, 0);
	return (process_register(&params->processes, pid));
}

t_error	params_wait(pid_t pid, int *status)
{
	t_params	*params;
	t_error		err;

	err = params_get_state(&params);
	if (err.type)
		return (err);
	return (process_wait(&params->processes, pid, status));
}

t_error	params_wait_all(int *status)
{
	t_params	*params;
	t_error		err;

	err = params_get_state(&params);
	if (err.type)
		return (err);
	return (process_wait_all(&params->processes, status));
}

t_error	params_reap(t_params *params)
{
	return (process_reap(&params->processes));
}
