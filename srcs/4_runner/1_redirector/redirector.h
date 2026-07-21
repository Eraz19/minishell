#ifndef REDIRECTOR_H
# define REDIRECTOR_H

# include "error.h"
# include "ast.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// TODO: doc
t_error	redirect_commit(const t_ast_redir_list *redirections, int *exit_status);

// TODO: doc
t_error	redirect_start(const t_ast_redir_list *redirections, int *exit_status);

// TODO: doc
t_error	redirect_stop(void);

#endif
