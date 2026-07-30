#ifndef REDIRECT_STACK_TYPE_H
# define REDIRECT_STACK_TYPE_H

# include "libft.h"

typedef struct s_redir_backup
{
	int	backup_fd;	// (-1 if fd was closed before redirection)
	int	fd;
}	t_redir_backup;

// vector(t_redir_backup)
typedef t_vector	t_redir_frame;

// vector(t_redir_frame)
typedef t_vector	t_redir_stack;

#endif
