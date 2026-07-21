#include "redirector_priv.h"
#include "fd.h"
#include <unistd.h>

#define CITATION_1	"POSIX 2.7.5 / 2.7.6: If word evaluates to something else "
#define CITATION_2	"[than a file descriptor or '-'], the behavior is unspecified"
#define CITATION	CITATION_1 CITATION_2
#define IMPLEMENT	"redirection error"

// @ret ERR_REDIRECTION
static inline t_error	redirect_dup_invalid_word(t_redir *redir)
{
	const char	*value;

	print_unspecified_behaviour(redir->word.value.data, CITATION, IMPLEMENT);
	if (redir->expanded_word.len == 0)
		value = "";
	else
		value = redir->expanded_word.data;
	return (error_print(error(ERR_REDIRECTION),
		"invalid file descriptor", NULL, "'%s' expanded from '%s'",
		value, redir->word.value.data));
}

// @ret ERR_REDIRECTION / ERR_LIBC
static inline t_error	redirect_validate_dup_rhs(t_redir *redir)
{
	int		rhs_fd;
	t_error	err;

	if (redir->expanded_word.len == 1 && redir->expanded_word.data[0] == '-')
		return (error(ERR_NO));
	else if (redir->expanded_word.len == 0
		|| redirect_parse_fd(redir->expanded_word.data, &rhs_fd) == false)
		return (redirect_dup_invalid_word(redir));
	err = fd_check_dup_rhs(rhs_fd);
	if (err.type == ERR_REDIRECTION)
		return (error_print(err,
			"file descriptor is not open", NULL,
			"%i expanded from '%s'", rhs_fd, redir->word.value.data));
	return (err);
}

t_error	redirect_prepare(t_redir *redirection, bool permanent)
{
	t_ast_redir_op	operation;
	t_error			err;

	operation = redirection->operation;
	if (operation == AST_REDIR_DUP_READ || operation == AST_REDIR_DUP_WRITE)
	{
		err = redirect_validate_dup_rhs(redirection);
		if (err.type)
			return (err);
	}
	if (permanent == true)
		return (fd_prepare_perm(redirection->fd));
	return (fd_save_temp(redirection->fd));
}
