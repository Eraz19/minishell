#include "redirector_priv.h"
#include "fd_manager.h"
#include <unistd.h>

// @ret ERR_POSIX_REDIRECTION
static inline t_error	redirect_dup_invalid_word(t_ast_redirection *redir)
{
	const char	*value;

	(void)undefined_behaviour("POSIX 2.7.5 / 2.7.6: "
		"If word evaluates to something else "
		"[than a file descriptor or '-'], "
		"the behavior is unspecified");
	if (redir->expanded_word.len == 0)
		value = "";
	else
		value = redir->expanded_word.data;
	return (error_print(error(ERR_POSIX_REDIRECTION), REDIRECTOR_MODULE_NAME,
		"invalid word value", NULL, "'%s' expanded from '%s'",
		value, redir->word->value.data));
}

// @ret ERR_POSIX_REDIRECTION / ERR_LIBC
static inline t_error	redirect_validate_dup_rhs(
							t_ast_redirection *redir,
							t_redirector *redirector)
{
	int		rhs_fd;
	t_error	err;

	if (redir->expanded_word.len == 1 && redir->expanded_word.data[0] == '-')
		return (error(ERR_NO));
	else if (redir->expanded_word.len == 0
		|| redirect_parse_fd(redir->expanded_word.data, &rhs_fd) == false)
		return (redirect_dup_invalid_word(redir));
	err = fd_check_dup_rhs(redirector, rhs_fd);
	if (err.type == ERR_POSIX_REDIRECTION)
		return (error_print(err,
			REDIRECTOR_MODULE_NAME, "file descriptor is not open", NULL,
			"%i expanded from '%s'", rhs_fd, redir->word->value.data));
	return (err);
}

t_error	redirect_prepare(
			t_ast_redirection *redirection,
			t_redirector *redirector,
			bool permanent)
{
	t_ast_redir_op	operation;
	t_error			err;

	operation = redirection->operation;
	if (operation == AST_REDIR_DUP_READ || operation == AST_REDIR_DUP_WRITE)
	{
		err = redirect_validate_dup_rhs(redirection, redirector);
		if (err.type)
			return (err);
	}
	if (permanent == true)
		return (fd_prepare_perm(redirector, redirection->fd));
	return (fd_save_temp(redirector, redirection->fd));
}
