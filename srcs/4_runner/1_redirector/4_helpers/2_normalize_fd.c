#include "redirector_priv.h"
#include <unistd.h>

// @ret ERR_POSIX_REDIRECTION
static inline t_error	redirect_convert_location(t_ast_redirection *redir)
{
	char		*content_start;
	size_t		last_char_index;
	char		last_char;
	bool		res;
	t_error		err;

	content_start = redir->expanded_location.data + 1;
	last_char_index = redir->expanded_location.len - 1;
	last_char = redir->expanded_location.data[last_char_index];
	redir->expanded_location.data[last_char_index] = '\0';
	res = redirect_parse_fd(content_start, &redir->fd);
	if (res == true)
		err = error(ERR_NO);
	else
		err = error_print(error(ERR_POSIX_REDIRECTION), REDIRECTOR_MODULE_NAME,
			"io_location is not a valid file descriptor", NULL,
			"'%s' expanded from '%s'",
			content_start, redir->location->value.data);
	redir->expanded_location.data[last_char_index] = last_char;
	return (err);
}

t_error	redirect_normalize_fd(t_ast_redirection *redirection)
{
	t_ast_redir_op	operation;

	if (redirection->is_location)
		return (redirect_convert_location(redirection));
	else if (redirection->fd >= 0)
		return error(ERR_NO);
	operation = redirection->operation;
	if (operation == AST_REDIR_READ
		|| operation == AST_REDIR_HEREDOC
		|| operation == AST_REDIR_DUP_READ
		|| operation == AST_REDIR_READ_WRITE)
		redirection->fd = STDIN_FILENO;
	else
		redirection->fd = STDOUT_FILENO;
	return error(ERR_NO);
}
