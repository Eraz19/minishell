#ifndef REDIRECTOR_PRIV_H
# define REDIRECTOR_PRIV_H

# include "error.h"
# include "ast.h"
# include "redirector_type.h"

# define REDIRECTOR_MODULE_NAME	"runner: redirector"

// Type

typedef struct s_redir
{
	t_ast_redir_op	operation;
	bool			expand_heredoc_body;
	int				fd;
	const t_token	*word;				// borrowed
	const t_string	*heredoc_body;		// borrowed
	t_string		expanded_word;		// or expanded heredoc_body
	bool			is_location;
	const t_token	*location;			// borrowed
	t_string		expanded_location;
}	t_redir;

// Life cycle

void	redir_init(t_redir *redir, const t_ast_redirection *src);
void	redir_free(t_redir *redir);

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
			const t_ast_redirection *redirection,
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
 * @brief Expand the word/heredoc body and optional io_location of redirection.
 *
 * @param redirection Redirection to expand (borrowed).
 * @return @c ERR_POSIX_EXPANSION, @c ERR_REDIRECTION, @c ERR_INTERNAL or @c ERR_LIBC.
 */
t_error	redirect_expand(t_redir *redirection);

// @ret ERR_REDIRECTION
t_error	redirect_resolve_location(t_redir *redir);

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
			t_redir *redirection,
			t_redirector *redirector,
			bool permanent);

// TODO: doc
// @ret ERR_REDIRECTION / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
t_error	redirect_open(t_redirector *redirector, t_redir *redir, int *out_fd);

// TODO: doc
// @ret ERR_REDIRECTION / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
t_error	redirect_get_heredoc_path(
			t_redirector *redirector,
			const t_string *body,
			char **out_path);

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
