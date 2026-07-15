#ifndef REDIRECTOR_H
# define REDIRECTOR_H

# include "error.h"
# include "ast.h"
# include "redirector_type.h"

/* ************************************************************************* */
/*                                 LIFE CYCLE                                */
/* ************************************************************************* */

/**
 * @brief Initialize an empty redirector state.
 *
 * @note @p redirector is initialized by the function.
 *
 * @param redirector Destination redirector (borrowed, initialized by the
 *                   function).
 */
void	redirect_init(t_redirector *redirector);

// TODO: doc
void	redirect_init_subshell(t_redirector *redirector);

// TODO: doc
// can't fail if restore_redirections = false
t_error	redirect_clear(t_redirector *redirector, bool restore_redirections);

/**
 * @brief Restore tracked file descriptors and free redirector resources.
 *
 * @param redirector Redirector to free (borrowed).
 */
void	redirect_free(t_redirector *redirector);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// TODO: doc
t_error	redirect_commit(
			t_redirector *redirector,
			const t_ast_redir_list *redirections,
			int *exit_status);

// TODO: doc
t_error	redirect_start(
			t_redirector *redirector,
			const t_ast_redir_list *redirections,
			int *exit_status);

/**
 * @brief Restore and discard the most recent temporary redirection frame.
 *
 * @param redirector Redirector state to restore (borrowed).
 * @return @c ERR_NO, @c ERR_INDEX_OUT_OF_BOUND, @c ERR_INTERRUPTED or
 *         @c ERR_LIBC.
 */
t_error	redirect_stop(t_redirector *redirector);

#endif
