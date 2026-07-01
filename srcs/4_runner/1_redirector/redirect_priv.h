#ifndef REDIRECT_PRIV_H
# define REDIRECT_PRIV_H

# include "redirect.h"
# include "error.h"

# define REDIRECT_MODULE_NAME	"runner: redirector"

typedef struct s_redir_backup
{
	int	backup_fd;	// (-1 if fd was closed before redirection)
	int	fd;
}	t_redir_backup;

typedef t_vector	t_redir_frame;

/* ************************************************************************* */
/*                                ENTRY POINT                                */
/* ************************************************************************* */

t_error	redirect_apply(t_ast_redirection *redirection, t_redir_frame *frame);

/* ************************************************************************* */
/*                                  HELPERS                                  */
/* ************************************************************************* */

t_error	redirect_expand(t_ast_redirection *redirection);
t_error	redirect_normalize_fd(t_ast_redirection *redir, t_redir_frame *frame);
t_error	redirect_create_backup(t_redir_backup *item, int fd);
t_error	redirect_restore_fds(t_redir_backup *backup);
t_error	redirect_open(t_ast_redirection *redir, int *out_fd);
bool	redirect_parse_fd(const char *s, int *out_fd);

/* ************************************************************************* */
/*                                   STACK                                   */
/* ************************************************************************* */

t_error	redirect_stack_push(t_redir_stack *stack, t_redir_frame *frame);
t_error	redirect_stack_pop(t_redir_stack *stack, t_redir_frame *out_frame);

/* ************************************************************************* */
/*                                   FRAME                                   */
/* ************************************************************************* */

void	redirect_frame_init(t_redir_frame *frame);
t_error	redirect_frame_push(t_redir_frame *frame, t_redir_backup *backup);
t_error	redirect_restore_frame(t_redir_frame *frame);
void	redirect_frame_free(void *frame);

#endif
