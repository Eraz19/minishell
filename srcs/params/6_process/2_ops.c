#include "process.h"
#include "posix_helpers.h"
#include <sys/wait.h>

t_error	process_register(t_process_table *table, pid_t pid)
{
	t_process	process;

	process.pid = pid;
	process.status = -1;
	if (!vector_push(table, &process))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	process_wait(t_process_table *table, pid_t pid, int *status)
{
	t_process	*process;
	size_t		i;
	t_error		err;

	i = 0;
	while (i < table->len)
	{
		process = &((t_process *)table->data)[i];
		if (process->pid == pid)
		{
			if (process->status < 0)
			{
				err = posix_wait(pid, &process->status);
				if (err.type)
					return (err);
			}
			*status = process->status;
			if (!vector_remove(table, i, NULL))
				return (error(ERR_INTERNAL));
			return (error(ERR_NO));
		}
		i++;
	}
	*status = 127;
	return (error(ERR_NO));
}

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
			wait_err = posix_wait(process->pid, &process->status);
			err = error_priorize(err, wait_err);
		}
		i++;
	}
	if (err.type)
		return (*status = (int)err.type, err);
	*status = 0;
	process_clear(table);
	return (err);
}

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
			err = error_priorize(err, wait_err);
		}
		i++;
	}
	return (err);
}
