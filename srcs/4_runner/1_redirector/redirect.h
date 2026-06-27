#ifndef REDIRECT_H
# define REDIRECT_H

# include "libft.h"
# include "ast_type.h"
# include "error.h"

typedef struct s_redir_frame
{
	t_vector	fds;		// vector of int
	t_vector	backup_fds;	// vector of int (-1 if fd was closed before redirection)
}	t_redir_frame;

typedef t_vector	t_redir_stack;

/* ---------- PUBLIC ---------- */

void	redirect_init(t_redir_stack *stack);
t_error	redirect_commit(t_ast_redir_list *redirections);
t_error	redirect_start(t_redir_stack *stack, t_ast_redir_list *redirections);
t_error	redirect_stop(t_redir_stack *stack);
void	redirect_free(t_redir_stack *stack);

#endif
