#ifndef REDIRECTOR_PRIV_H
# define REDIRECTOR_PRIV_H

# include "error.h"
# include "ast.h"
# include "redirector_type.h"

# define REDIRECTOR_MODULE_NAME	"runner: redirector"

/* ************************************************************************* */
/*                                ENTRY POINT                                */
/* ************************************************************************* */

/**
 * @brief Expand, normalize, prepare and apply one redirection.
 *
 * When @p permanent is @c false, backup state is rolled back on application
 * failure. When @p permanent is @c true, successful backups are kept inside
 * @p redirector.
 *
 * @param redirection Redirection to apply (borrowed).
 * @param redirector Redirector state used to track backups (borrowed).
 * @param permanent True for committed redirections, false for restorable ones.
 * @return @c ERR_NO, @c ERR_REDIRECTION, @c ERR_INCOHERENT_STATE,
 *         @c ERR_INVALID_USAGE, @c ERR_INTERRUPTED,
 *         @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME,
 *         @c ERR_VAR_NOT_FOUND, @c ERR_PARAM_BAD_SUBSTITUTION,
 *         @c ERR_PARAM_NULL_OR_UNSET, @c ERR_NOT_IMPLEMENTED,
 *         @c ERR_EXP_RESULT_INCOHERENT, @c ERR_QUOTED_TILDE or @c ERR_LIBC.
 */
t_error	redirect_apply(
			t_ast_redirection *redirection,
			t_redirector *redirector,
			bool permanent);

/* ************************************************************************* */
/*                                  HELPERS                                  */
/* ************************************************************************* */

/**
 * @brief Parse a decimal file descriptor number.
 *
 * @param s NUL-terminated decimal representation to parse
 *          (borrowed, read-only).
 * @param out_fd Destination receiving the parsed file descriptor or @c -1 on
 *               failure (borrowed).
 * @return True on success, false on invalid syntax or overflow.
 */
bool	redirect_parse_fd(const char *s, int *out_fd);

/**
 * @brief Expand the word and optional io_location of one redirection.
 *
 * @note On success, expanded strings are stored directly inside
 *       @p redirection.
 *
 * @param redirection Redirection to expand (borrowed).
 * @return @c ERR_NO, @c ERR_REDIRECTION, @c ERR_SHELL_NOT_FOUND,
 *         @c ERR_VAR_INVALID_NAME, @c ERR_VAR_NOT_FOUND,
 *         @c ERR_PARAM_BAD_SUBSTITUTION, @c ERR_PARAM_NULL_OR_UNSET,
 *         @c ERR_NOT_IMPLEMENTED, @c ERR_INCOHERENT_STATE,
 *         @c ERR_EXP_RESULT_INCOHERENT, @c ERR_QUOTED_TILDE or @c ERR_LIBC.
 */
t_error	redirect_expand(t_ast_redirection *redirection);

/**
 * @brief Resolve the effective target file descriptor of one redirection.
 *
 * @param redirection Redirection to normalize (borrowed).
 * @return @c ERR_NO or @c ERR_REDIRECTION.
 */
t_error	redirect_normalize_fd(t_ast_redirection *redirection);

/**
 * @brief Prepare backup state before one redirection is applied.
 *
 * @param redirection Redirection being prepared (borrowed).
 * @param redirector Redirector state used to track backups (borrowed).
 * @param permanent True for committed redirections, false for temporary ones.
 * @return @c ERR_NO, @c ERR_REDIRECTION, @c ERR_INCOHERENT_STATE or
 *         @c ERR_LIBC.
 */
t_error	redirect_prepare(
			t_ast_redirection *redirection,
			t_redirector *redirector,
			bool permanent);

/**
 * @brief Open the file targeted by a non-duplication redirection.
 *
 * @param redirection Redirection describing the path and mode (borrowed).
 * @param out_fd Destination receiving the opened file descriptor (borrowed).
 * @return @c ERR_NO, @c ERR_REDIRECTION, @c ERR_INVALID_USAGE,
 *         @c ERR_INTERRUPTED, @c ERR_SHELL_NOT_FOUND or @c ERR_LIBC.
 */
t_error	redirect_open(t_ast_redirection *redirection, int *out_fd);

/* ************************************************************************* */
/*                                   ERRORS                                  */
/* ************************************************************************* */

/**
 * @brief Print a redirector-scoped error message.
 *
 * @param message Message suffix to print (borrowed, read-only).
 * @return Error descriptor carrying @c ERR_REDIRECTION.
 */
t_error	redirect_print_error(const char *message);

/**
 * @brief Print the standard "all file descriptors are already used" error.
 *
 * @return Error descriptor carrying @c ERR_REDIRECTION.
 */
t_error	redirect_print_error_all_fd_used(void);

#endif
