/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_open.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 15:20:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:23:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirector_priv.h"
#include "ast.h"
#include "options.h"
#include "posix_helpers.h"
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
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

// @ret ERR_INVALID_USAGE / ERR_REDIRECTION / ERR_INTERRUPTED / ERR_LIBC
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
		(void)error_print(error_sys(),
			"redirection failed", "no clobber is active and file exists",
			"unable to stat file", NULL,
			"'%s' expanded from '%s'", path, redir->word.value.data);
		err = error(ERR_REDIRECTION);
		err.printed = true;
		return (err);
	}
	else if (S_ISREG(st.st_mode))
		return (error_print(error(ERR_REDIRECTION),
				"no clobber is active and file is regular", NULL,
				"'%s' expanded from '%s'", path, redir->word.value.data));
	oflag = O_WRONLY | O_CREAT | O_TRUNC;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	return (posix_open_with_mode(path, oflag, mode, out_fd));
}

static inline void	redirect_unlink_heredoc(char *path)
{
	if (unlink(path) != 0)
		(void)error_print(error_sys(),
			"unable to unlink heredoc file", NULL, "'%s'", path);
	free(path);
}

// @ret ERR_REDIRECTION / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
static inline t_error	redirect_handle_open_error(
							t_redir *redir,
							bool no_clobber,
							int *out_fd,
							t_error err)
{
	const char	*path;

	if (err.type == ERR_LIBC && err.saved_errno == EEXIST
		&& redir->operation == AST_REDIR_WRITE && no_clobber)
	{
		path = redir->expanded_word.data;
		err = redirect_handle_noclobber_eexist(redir, path, out_fd);
		if (err.type == ERR_NO)
			return (err);
	}
	if (err.type && redir->operation == AST_REDIR_HEREDOC)
	{
		err = error_print(err, "redirection failed",
				"unable to open heredoc file", NULL, NULL);
	}
	else if (err.type)
	{
		err = error_print(err, "redirection failed",
				"unable to open file", NULL, "'%s' expanded from '%s'",
				redir->expanded_word.data, redir->word.value.data);
	}
	if (err.type && err.type != ERR_INVALID_USAGE && err.type != ERR_INTERNAL
		&& err.type != ERR_INTERRUPTED)
		err.type = ERR_REDIRECTION;
	return (err);
}

t_error	redirect_open(t_redir *redir, int *out_fd)
{
	bool	no_clobber;
	char	*path;
	int		oflag;
	t_error	err;

	err = option_is_active(OPT_NOCLOBBER, &no_clobber);
	if (err.type == ERR_NO && redir->operation == AST_REDIR_HEREDOC)
		err = redirect_prepare_heredoc_file(&redir->expanded_word, &path);
	else
		path = redir->expanded_word.data;
	if (err.type)
		return (err);
	oflag = redirect_get_oflag(redir->operation, no_clobber);
	if (redir->operation == AST_REDIR_WRITE
		|| redir->operation == AST_REDIR_CLOBBER
		|| redir->operation == AST_REDIR_APPEND
		|| redir->operation == AST_REDIR_READ_WRITE)
		err = posix_open_with_mode(path, oflag, S_IRUSR | S_IWUSR | S_IRGRP
				| S_IWGRP | S_IROTH | S_IWOTH, out_fd);
	else
		err = posix_open(path, oflag, out_fd);
	if (redir->operation == AST_REDIR_HEREDOC)
		redirect_unlink_heredoc(path);
	return (redirect_handle_open_error(redir, no_clobber, out_fd, err));
}
