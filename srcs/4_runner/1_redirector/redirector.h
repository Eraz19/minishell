#ifndef REDIRECTOR_H
# define REDIRECTOR_H

# include "error.h"
# include "ast_type.h"
# include "redirector_type.h"

/* ************************************************************************* */
/*                                 LIFE CYCLE                                */
/* ************************************************************************* */

void	redirect_init(t_redirector *redirector);
void	redirect_free(t_redirector *redirector);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @ret ERR_REDIRECTION_FAILED / ERR_INCOHERENT_STATE
// 		/ ERR_OPEN_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
t_error	redirect_commit(t_redirector *redirector, t_ast_redir_list *redirections);

// @ret ERR_REDIRECTION_FAILED / ERR_INCOHERENT_STATE
// 		/ ERR_OPEN_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
t_error	redirect_start(t_redirector *redirector, t_ast_redir_list *redirections);

// @ret ERR_INDEX_OUT_OF_BOUND / ERR_INTERRUPTED / ERR_LIBC
t_error	redirect_stop(t_redirector *redirector);

#endif
