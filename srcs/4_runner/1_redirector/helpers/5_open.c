#include "redirect_priv.h"
#include "ast_type.h"
#include "options.h"
#include "posix_helpers.h"
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

static inline t_error	redirect_handle_open_error(
							t_ast_redirection *redir,
							const char *path,
							t_error err)
{
	if (err.type == ERR_NO)
		return (err);
	if (redir->operation == AST_REDIR_HEREDOC)
		(void)error_print(err, REDIRECT_MODULE_NAME,
			"redirection failed", "unable to open heredoc file", NULL, NULL);
	else
		(void)error_print(err, REDIRECT_MODULE_NAME,
			"redirection failed", "unable to open file", NULL,
			"'%s' expanded from '%s'", path, redir->word->value.data);
	err = error(ERR_REDIRECTION_FAILED);
	err.printed = true;
	return (err);
}

static inline int	redirect_get_oflag(t_ast_redir_op op, bool no_clobber)
{
	int	oflag;

	oflag = 0;
	if (op == AST_REDIR_READ || op == AST_REDIR_HEREDOC)
		oflag = O_RDONLY;
	else if (op == AST_REDIR_WRITE || op == AST_REDIR_CLOBBER)
	{
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
		if (op == AST_REDIR_WRITE && no_clobber)
			oflag |= O_EXCL;
	}
	else if (op == AST_REDIR_APPEND)
		oflag = O_WRONLY | O_CREAT | O_APPEND;
	else if (op == AST_REDIR_READ_WRITE)
		oflag = O_RDWR | O_CREAT;
	return (oflag);
}

static inline t_error	redirect_open_with_flags_and_mode(
							t_ast_redirection *redir,
							const char *path,
							bool no_clobber,
							int *out_fd)
{
	int				oflag;
	mode_t			mode;

	oflag = redirect_get_oflag(redir->operation, no_clobber);
	if (redir->operation == AST_REDIR_WRITE
		|| redir->operation == AST_REDIR_CLOBBER
		|| redir->operation == AST_REDIR_APPEND
		|| redir->operation == AST_REDIR_READ_WRITE)
	{
		mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
		return (posix_open_with_mode(path, oflag, mode, out_fd));
	}
	return (posix_open(path, oflag, out_fd));
}

static inline t_error	redirect_open_and_convert_error(
							t_ast_redirection *redir,
							const char *path,
							bool no_clobber,
							int *out_fd)
{
	t_error	err;

	err = redirect_open_with_flags_and_mode(redir, path, no_clobber, out_fd);
	if (err.type == ERR_LIBC && err.saved_errno == EEXIST
		&& redir->operation == AST_REDIR_WRITE && no_clobber)
	{
		// TODO: check if path is a regular file or a symlink to regular file
		//			=> if true	=> redirection error
		//			=> else		=> retry open without O_EXCL
		return (error_print(error(ERR_REDIRECTION_FAILED),
			REDIRECT_MODULE_NAME, "no clobber is active and file exists", NULL,
			"%s", redir->expanded_word.data));
	}
	return (redirect_handle_open_error(redir, path, err));
}

t_error	redirect_open(t_ast_redirection *redir, int *out_fd)
{
	bool		no_clobber;
	const char	*path;
	t_error		err;

	err = option_is_active(OPT_NOCLOBBER, &no_clobber);
	if (err.type)
		return (err);
	if (redir->operation == AST_REDIR_HEREDOC)
		path = redir->word->value.data;
	else
		path = redir->expanded_word.data;
	return (redirect_open_and_convert_error(redir, path, no_clobber, out_fd));
}
