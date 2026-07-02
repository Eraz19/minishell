#ifndef REDIRECTOR_PRIV_H
# define REDIRECTOR_PRIV_H

# include "error.h"
# include "ast_type.h"
# include "redirector_type.h"

# define REDIRECTOR_MODULE_NAME	"runner: redirector"

/* ************************************************************************* */
/*                                ENTRY POINT                                */
/* ************************************************************************* */

// @ret ERR_REDIRECTION_FAILED / ERR_INCOHERENT_STATE
// 		/ ERR_OPEN_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
t_error	redirect_apply(
			t_ast_redirection *redirection,
			t_redirector *redirector,
			bool permanent);

/* ************************************************************************* */
/*                                  HELPERS                                  */
/* ************************************************************************* */

bool	redirect_parse_fd(const char *s, int *out_fd);

// @ret TODO (expander has no doc yet)
t_error	redirect_expand(t_ast_redirection *redirection);

// @ret ERR_REDIRECTION_FAILED
t_error	redirect_normalize_fd(t_ast_redirection *redirection);

// @ret ERR_REDIRECTION_FAILED / ERR_INCOHERENT_STATE / ERR_LIBC
t_error	redirect_prepare(
			t_ast_redirection *redirection,
			t_redirector *redirector,
			bool permanent);

// @ret ERR_REDIRECTION_FAILED / ERR_OPEN_INVALID_USAGE / ERR_INTERRUPTED
// 		/ ERR_LIBC
t_error	redirect_open(t_ast_redirection *redirection, int *out_fd);

/* ************************************************************************* */
/*                                   ERRORS                                  */
/* ************************************************************************* */

// @ret ERR_REDIRECTION_FAILED
t_error	redirect_print_error(const char *message);

// @ret ERR_REDIRECTION_FAILED
t_error	redirect_print_error_all_fd_used(void);

#endif
