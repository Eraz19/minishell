#include "redirector_priv.h"
#include "ast.h"
#include "options.h"
#include "posix_helpers.h"
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

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

// @ret ERR_REDIRECTION / ERR_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
static inline t_error	redirect_handle_noclobber_eexist(
							t_redir *redir,
							const char *path,
							int *out_fd)
{
	struct stat	st;
	int			oflag;
	mode_t		mode;
	t_error		err;

	if (stat(path, &st) == -1)
	{
		(void)error_print(error_sys(), REDIRECTOR_MODULE_NAME,
			"redirection failed", "no clobber is active and file exists",
			"unable to stat file", NULL,
			"'%s' expanded from '%s'", path, redir->word->value.data);
		err = error(ERR_REDIRECTION);
		err.printed = true;
		return (err);
	}
	else if (S_ISREG(st.st_mode))
		return (error_print(error(ERR_REDIRECTION),
			REDIRECTOR_MODULE_NAME,
			"no clobber is active and file is regular", NULL,
			"'%s' expanded from '%s'", path, redir->word->value.data));
	oflag = O_WRONLY | O_CREAT | O_TRUNC;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	return (posix_open_with_mode(path, oflag, mode, out_fd));
}

// @ret ERR_REDIRECTION
static inline t_error	redirect_handle_open_error(
							t_redir *redir,
							bool no_clobber,
							int *out_fd,
							t_error err)
{
	const char	*path;

	if (err.type == ERR_NO)
		return (err);
	else if (redir->operation == AST_REDIR_HEREDOC)
	{
		(void)error_print(err, REDIRECTOR_MODULE_NAME, "redirection failed",
			"unable to open heredoc file", NULL, NULL);
		return (err = error(ERR_REDIRECTION), err.printed = true, err);
	}
	else if (err.type == ERR_LIBC && err.saved_errno == EEXIST
		&& redir->operation == AST_REDIR_WRITE && no_clobber)
	{
		path = redir->expanded_word.data;
		err = redirect_handle_noclobber_eexist(redir, path, out_fd);
		if (err.type == ERR_NO)
			return (err);
	}
	if (err.type && err.printed == false)
		(void)error_print(err, REDIRECTOR_MODULE_NAME, "redirection failed",
			"unable to open file", NULL, "'%s' expanded from '%s'",
			redir->expanded_word.data, redir->word->value.data);
	return (err = error(ERR_REDIRECTION), err.printed = true, err);
}

t_error	redirect_open(t_redir *redirection, int *out_fd)
{
	bool		no_clobber;
	const char	*path;
	int			oflag;
	mode_t		mode;
	t_error		err;

	err = option_is_active(OPT_NOCLOBBER, &no_clobber);
	if (err.type)
		return (err);
	if (redirection->operation == AST_REDIR_HEREDOC)
		path = redirection->word->value.data;
	else
		path = redirection->expanded_word.data;
	oflag = redirect_get_oflag(redirection->operation, no_clobber);
	if (redirection->operation == AST_REDIR_WRITE
		|| redirection->operation == AST_REDIR_CLOBBER
		|| redirection->operation == AST_REDIR_APPEND
		|| redirection->operation == AST_REDIR_READ_WRITE)
	{
		mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
		err = posix_open_with_mode(path, oflag, mode, out_fd);
	}
	else
		err = posix_open(path, oflag, out_fd);
	return (redirect_handle_open_error(redirection, no_clobber, out_fd, err));
}
