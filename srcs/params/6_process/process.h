#ifndef PROCESS_H
# define PROCESS_H

# include "libft.h"
# include "error.h"
# include <sys/types.h>

// TODO: doc

typedef struct s_process
{
	pid_t	pid;
	int		status;	// default = -1
}	t_process;

// t_vector of t_process
typedef t_vector t_process_table;

// life cycle

void	process_init(t_process_table *table);
void	process_clear(t_process_table *table);
void	process_free(t_process_table *table);

// ops

t_error	process_register(t_process_table *table, pid_t pid);
t_error	process_wait(t_process_table *table, pid_t pid, int *status);
t_error	process_wait_all(t_process_table *table, int *status);

// @ret ERR_LIBC / ERR_INTERRUPTED
t_error	process_reap(t_process_table *table);

#endif
