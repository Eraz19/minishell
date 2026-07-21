#ifndef REDIRECTOR_PRIV_H
# define REDIRECTOR_PRIV_H

# include "error.h"
# include "ast.h"

// Type

typedef struct s_redir
{
	t_ast_redir_op	operation;
	bool			expand_heredoc_body;
	int				fd;
	t_token			word;
	const t_string	*heredoc_body;		// borrowed
	t_string		expanded_word;		// or expanded heredoc_body
	bool			is_location;
	t_token			location;
	t_string		expanded_location;
}	t_redir;

// Life cycle

t_error	redir_init(t_redir *redir, const t_ast_redirection *src);
void	redir_free(t_redir *redir);

/* ************************************************************************* */
/*                                ENTRY POINT                                */
/* ************************************************************************* */

// TODO: doc
t_error	redirect_apply(
			const t_ast_redirection *redirection,
			bool permanent,
			int *exit_status);

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

// TODO: doc
// @return @c ERR_POSIX_EXPANSION, @c ERR_REDIRECTION, @c ERR_INTERNAL or @c ERR_LIBC.
t_error	redirect_expand(t_redir *redirection, int *exit_status);

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
t_error	redirect_prepare(t_redir *redirection, bool permanent);

// TODO: doc
// @ret ERR_REDIRECTION / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
t_error	redirect_open(t_redir *redir, int *out_fd);

// TODO: doc
// @ret ERR_REDIRECTION / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
t_error	redirect_prepare_heredoc_file(const t_string *body, char **out_path);

#endif
