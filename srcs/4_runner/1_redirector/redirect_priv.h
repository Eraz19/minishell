#ifndef REDIRECT_PRIV_H
# define REDIRECT_PRIV_H

# include "redirect.h"
# include "error.h"

// frame

void	redirect_frame_init(t_redir_frame *frame);
t_error	redirect_push(t_redir_stack *stack, t_redir_frame *frame);
t_error	redirect_pop(t_redir_stack *stack);
void	redirect_frame_free(void *frame);

// redirection

t_error	redirect_prepare(t_ast_redirection *redirection, int *backup_fd);
t_error	redirect_apply(t_redir_stack *stack, t_redir_frame *frame);

#endif
