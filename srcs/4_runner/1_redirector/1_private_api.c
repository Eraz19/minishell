#include "redirect_priv.h"
#include "posix_helpers.h"
#include <unistd.h>
#include <errno.h>

static inline t_error	redirect_dup_invalid_word(t_ast_redirection *redir)
{
	(void)undefined_behaviour("POSIX 2.7.5 / 2.7.6: "
		"If word evaluates to something else "
		"[than a file descriptor or '-'], "
		"the behavior is unspecified");
	return (error_print(error(ERR_REDIRECTION_FAILED), REDIRECT_MODULE_NAME,
		"invalid word value", NULL, "'%s' expanded from '%s'",
		redir->expanded_word.data, redir->word->value.data));
}

static inline t_error	redirect_close(
							t_ast_redirection *redir,
							t_redir_frame *frame)
{
	t_redir_backup	backup;
	t_error			err;

	if (frame != NULL)
	{
		err = redirect_create_backup(&backup, redir->fd);
		if (err.type)
			return (err);
	}
	err = posix_close(redir->fd);
	if (err.type == ERR_LIBC && err.saved_errno == EBADF)
		err = error(ERR_NO);
	if (frame == NULL)
		return (err);
	else if (err.type)
	{
		(void)posix_close(backup.backup_fd);
		return (err);
	}
	return (redirect_frame_push(frame, &backup));
}

static inline t_error	redirect_dup(
							t_ast_redirection *redir,
							t_redir_frame *frame)
{
	t_redir_backup	backup;
	int				rhs_fd;
	t_error			err;

	if (redir->expanded_word.len == 0)
		return (redirect_dup_invalid_word(redir));
	else if (str_cmp(redir->expanded_word.data, "-") == 0)
		return (redirect_close(redir, frame));
	else if (!redirect_parse_fd(redir->expanded_word.data, &rhs_fd))
		return (redirect_dup_invalid_word(redir));
	if (frame != NULL)
	{
		err = redirect_create_backup(&backup, redir->fd);
		if (err.type)
			return (err);
	}
	err = posix_dup2(rhs_fd, redir->fd);
	if (err.type == ERR_LIBC && err.saved_errno == EBADF)
		err = error_print(error(ERR_REDIRECTION_FAILED), REDIRECT_MODULE_NAME,
			"file descriptor is not valid", NULL, "%i", rhs_fd);
	else if (err.type == ERR_NO)
		return (redirect_frame_push(frame, &backup));
	if (frame != NULL && backup.backup_fd >= 0)
		(void)posix_close(backup.backup_fd);
	return (err);
}

static inline t_error	redirect_redirect(
							t_ast_redirection *redir,
							int opened_fd,
							t_redir_frame *frame)
{
	t_redir_backup	backup;
	t_error			err;

	if (frame != NULL)
	{
		err = redirect_create_backup(&backup, redir->fd);
		if (err.type)
			return ((void)posix_close(opened_fd), err);
	}
	err = posix_dup2(opened_fd, redir->fd);
	if (err.type)
	{
		(void)posix_close(opened_fd);
		if (frame != NULL && backup.backup_fd >= 0)
			(void)posix_close(backup.backup_fd);
		return (err);
	}
	err = posix_close(opened_fd);
	if (err.type && err.saved_errno != EBADF)
	{
		if (frame != NULL)
			(void)redirect_restore_fds(&backup);
		return (err);
	}
	return (redirect_frame_push(frame, &backup));
}

t_error	redirect_apply(t_ast_redirection *redir, t_redir_frame *frame)
{
	t_ast_redir_op	operation;
	int				opened_fd;
	t_redir_backup	backup;
	t_error			err;

	err = redirect_expand(redir);
	if (err.type == ERR_NO)
		err = redirect_normalize_fd(redir, frame);
	if (err.type)
		return (err);
	operation = redir->operation;
	if (operation == AST_REDIR_DUP_READ || operation == AST_REDIR_DUP_WRITE)
		return (redirect_dup(redir, frame));
	err = redirect_open(redir, &opened_fd);
	if (err.type)
		return (err);
	else if (opened_fd != redir->fd)
		return (redirect_redirect(redir, opened_fd, frame));
	else if (frame != NULL)
	{
		backup.backup_fd = -1;
		backup.fd = redir->fd;
		return (redirect_frame_push(frame, &backup));
	}
	return (err);
}
