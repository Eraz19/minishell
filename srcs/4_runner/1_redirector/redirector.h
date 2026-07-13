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

/**
 * @brief Restore tracked file descriptors and free redirector resources.
 *
 * @param redirector Redirector to free (borrowed).
 */
void	redirect_free(t_redirector *redirector);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Close every backup file descriptor currently stored in the redirector.
 *
 * This is a best-effort cleanup helper intended for child processes before
 * @c execve(), since backup descriptors cannot currently be marked
 * @c FD_CLOEXEC.
 *
 * @note The logical redirection stack is left unchanged; only backup file
 *       descriptors are closed.
 *
 * @param redirector Redirector state whose backup file descriptors must be
 *                   closed (borrowed).
 */
void	redirect_close_backups(t_redirector *redirector);

/**
 * @brief Apply redirections permanently to the current process.
 *
 * Successful permanent redirections are recorded inside @p redirector so they
 * can later be restored by @ref redirect_free().
 *
 * @param redirector Redirector state used to track backups (borrowed).
 * @param redirections Redirection list to apply (borrowed).
 * @return @c ERR_NO, @c ERR_REDIRECTION, @c ERR_INCOHERENT_STATE,
 *         @c ERR_INVALID_USAGE, @c ERR_INTERRUPTED,
 *         @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME,
 *         @c ERR_VAR_NOT_FOUND, @c ERR_PARAM_BAD_SUBSTITUTION,
 *         @c ERR_PARAM_NULL_OR_UNSET, @c ERR_NOT_IMPLEMENTED,
 *         @c ERR_EXP_RESULT_INCOHERENT, @c ERR_QUOTED_TILDE or @c ERR_LIBC.
 */
t_error	redirect_commit(t_redirector *redirector, const t_ast_redir_list *redirections);

/**
 * @brief Apply redirections temporarily within a new restorable frame.
 *
 * When one redirection fails, every redirection already applied in the current
 * frame is rolled back before the function returns.
 *
 * @param redirector Redirector state used to track backups (borrowed).
 * @param redirections Redirection list to apply (borrowed).
 * @return @c ERR_NO, @c ERR_REDIRECTION, @c ERR_INCOHERENT_STATE,
 *         @c ERR_INVALID_USAGE, @c ERR_INTERRUPTED,
 *         @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME,
 *         @c ERR_VAR_NOT_FOUND, @c ERR_PARAM_BAD_SUBSTITUTION,
 *         @c ERR_PARAM_NULL_OR_UNSET, @c ERR_NOT_IMPLEMENTED,
 *         @c ERR_EXP_RESULT_INCOHERENT, @c ERR_QUOTED_TILDE or @c ERR_LIBC.
 */
t_error	redirect_start(t_redirector *redirector, const t_ast_redir_list *redirections);

/**
 * @brief Restore and discard the most recent temporary redirection frame.
 *
 * @param redirector Redirector state to restore (borrowed).
 * @return @c ERR_NO, @c ERR_INDEX_OUT_OF_BOUND, @c ERR_INTERRUPTED or
 *         @c ERR_LIBC.
 */
t_error	redirect_stop(t_redirector *redirector);

#endif
