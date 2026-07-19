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

// @ret ERR_NO / ERR_LIBC
t_error	process_register(t_process_table *table, pid_t pid);

// @ret ERR_NO / ERR_LIBC
t_error	process_wait(t_process_table *table, pid_t pid, int *status);

// @ret ERR_NO / ERR_LIBC
t_error	process_wait_all(t_process_table *table, int *status);

// @ret ERR_NO / ERR_LIBC
t_error	process_reap(t_process_table *table);

#endif
