#include "ast_type.h"
#include "expander.h"
#include "options.h"
#include "posix_helpers.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

/* ---------- CORRECT I GUESS ---------- */

static inline void	redirect_normalize_fd(t_ast_redirection *redirection)
{
	t_ast_redir_op	operation;

	if (redirection->fd != -1)
		return ;
	operation = redirection->operation;
	if (operation == AST_REDIR_READ
		|| operation == AST_REDIR_HEREDOC
		|| operation == AST_REDIR_DUP_READ
		|| operation == AST_REDIR_READ_WRITE)
		redirection->fd = STDIN_FILENO;
	redirection->fd = STDOUT_FILENO;
}

static inline t_error	redirect_expand(t_ast_redirection *redirection)
{
	t_vector	out;
	t_error		err;

	if (redirection->operation == AST_REDIR_HEREDOC
		&& redirection->expand_heredoc_body)
		err = expander_expand_heredoc_body(&redirection->word);
	else
		err = expander_expand_filename(&redirection->word, &out);
	if (err.type == ERR_NO && redirection->is_location)
		err = expander_expand_filename(&redirection->location);
	return (err);
}

static inline t_error	redirect_check_word(t_ast_redirection *redirection)
{
	size_t	i;
	t_buff	*word;

	if (redirection->operation != AST_REDIR_DUP_READ
		&& redirection->operation != AST_REDIR_DUP_WRITE)
		return (error(ERR_NO));
	word = &redirection->word;
	if (word->len == 1 && word->data[0] == '-')
		return (error(ERR_NO));
	i = 0;
	while (i < word->len)
	{
		if (ft_isdigit(word->data[i]) == 0)
			return (undefined_behaviour("POSIX 2.7.5 / 2.7.6: "
				"If word evaluates to something else "
				"[than a file descripto or '-'], the behavior is unspecified"));
		i++;
	}
	return (error(ERR_NO));
}

static inline t_error	redirect_create_backup_fd(int fd, int *backup_fd)
{
	*backup_fd = dup(fd);
	if (*backup_fd != -1 || errno == EBADF)
		return (error(ERR_NO));
	return (error_sys());
}

static inline int	redirect_get_oflag(
	t_ast_redirection *redirection,
	bool no_clobber_is_active)
{
	int				oflag;
	t_ast_redir_op	op;

	op = redirection->operation;
	oflag = 0;
	if (op == AST_REDIR_READ || op == AST_REDIR_HEREDOC)
		oflag = O_RDONLY;
	else if (op == AST_REDIR_WRITE)
	{
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
		if (no_clobber_is_active)
			oflag |= O_EXCL;
	}
	else if (op == AST_REDIR_APPEND)
		oflag = O_WRONLY | O_CREAT | O_APPEND;
	else if (op == AST_REDIR_CLOBBER)
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
	else if (op == AST_REDIR_READ_WRITE)
		oflag = O_RDWR | O_CREAT;
	return (oflag);
}

/* ---------- WIP ---------- */

static inline t_error	redirect_get_source_fd(
	t_ast_redirection *redirection,
	int *out)
{
	bool			no_clobber_is_active;
	int				oflag;
	char			*path;
	t_ast_redir_op	op;
	t_error			err;

	err = option_is_active(OPT_NOCLOBBER, &no_clobber_is_active);
	if (err.type)
		return (err);
	oflag = redirect_get_oflag(redirection, no_clobber_is_active);
	path = buff_get_string(&redirection->word);
	if (!path)
		return (error_sys());
	err = posix_open(path, oflag, out);
	free(path);
	op = redirection->operation;
	if (err.type == ERR_LIBC && errno == EBADF
		&& (op == AST_REDIR_DUP_READ || op == AST_REDIR_DUP_WRITE))
	{	 
		err = error(ERR_REDIRECTION_FAILED);
		return (error_print(err, "redirector", "fd is not open", NULL, NULL));
	}
	// TODO:
	if (*out == -1 && op == AST_REDIR_WRITE && no_clobber_is_active)
	{
		if (errno == EEXIST && !is_a_regular_file(path))
			// TODO: open as non-regular file (what does it mean ?!)
		err = error(ERR_REDIRECTION_FAILED);
		return (error_print(err, "redirector", "TODO", NULL, NULL));
		// Output redirection using the '>' format shall fail if the noclobber option is set (see the description of set -C) and the file named by the expansion of word exists and is either a regular file or a symbolic link that resolves to a regular file; it may also fail if the file is a symbolic link that does not resolve to an existing file. The check for existence, file creation, and open operations shall be performed atomically as is done by the open() function as defined in System Interfaces volume of POSIX.1-2024 when the O_CREAT and O_EXCL flags are set, except that if the file exists and is a symbolic link, the open operation need not fail with [EEXIST] unless the symbolic link resolves to an existing regular file
	}
	return (error(ERR_NO));
}

static inline t_error	redirect_push_to_frame(
	t_redir_frame *frame,
	int backup_fd,
	int new_fd)
{
	if (!vector_push(&frame->backup_fds, &backup_fd))
		return (error_sys());
	if (!vector_push(&frame->fds, &new_fd))
		return (error_sys());
	// TODO: restore fds on error
	return (error(ERR_NO));
}

t_error	redirect_apply(t_ast_redirection *redirection, t_redir_frame *frame)
{
	int		backup_fd;
	int		source_fd;
	int		new_fd;
	t_error	err;

	redirect_normalize_fd(redirection);
	err = redirect_expand(redirection);
	if (err.type == ERR_NO)
		err = redirect_check_word(redirection);
	if (err.type == ERR_NO)
		err = redirect_create_backup_fd(redirection->fd, &backup_fd);
	if (err.type == ERR_NO)
		err = redirect_get_source_fd(redirection, &source_fd);
	if (err.type)
		return (err);
	new_fd = dup2(source_fd, redirection->fd);
	// TODO: check dup2 return value ?
	// TODO: check that file is open for input or output ?
	if (redirection->operation != AST_REDIR_DUP_READ
		&& redirection->operation != AST_REDIR_DUP_WRITE)
		close(source_fd);
	return (redirect_push_to_frame(frame, backup_fd, new_fd));
}
