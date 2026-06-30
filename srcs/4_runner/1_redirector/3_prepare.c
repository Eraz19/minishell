#include "ast_type.h"
#include "expander.h"
#include "redirect_priv.h"
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

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
	t_expansion	out;
	int			flags;
	t_string	*expanded_word;
	t_error		err;

	flags = EXP_TILDE | EXP_PARAM | EXP_CMD_SUB | EXP_ARITHM_SUB | EXP_QUOTE;
	if (redirection->operation == AST_REDIR_HEREDOC
		&& redirection->expand_heredoc_body)
		err = heredoc_expand(&redirection->word->value);
	else
	{
		err = expander_expand(redirection->word, flags, &out);
		if (err.type)
			return (err);
		if (out.len > 1)
		{
			vector_free(&out, string_free_void);
			return (error_print(error(ERR_REDIRECTION_FAILED), "runner",
				"redirection word expands to more than one field", NULL, NULL));
		}
		err = expansion_get(&out, 0, &expanded_word);
		if (err.type)
			return (err);
		string_take(
			&redirection->expanded_word,
			expanded_word->data,
			expanded_word->cap,
			(ssize_t)expanded_word->len);
	}
	if (err.type == ERR_NO && redirection->is_location)
		err = expander_expand_filename(redirection->location, &out);
	return (err);
}

static inline t_error	redirect_check_word(t_ast_redirection *redirection)
{
	size_t		i;
	t_string	*word;

	if (redirection->operation != AST_REDIR_DUP_READ
		&& redirection->operation != AST_REDIR_DUP_WRITE)
		return (error(ERR_NO));
	word = &redirection->word->value;
	if (word->len == 1 && word->data[0] == '-')
		return (error(ERR_NO));
	i = 0;
	while (i < word->len)
	{
		if (ft_isdigit(word->data[i]) == 0)
			return (undefined_behaviour("POSIX 2.7.5 / 2.7.6: "
				"If word evaluates to something else "
				"[than a file descriptor or '-'], "
				"the behavior is unspecified"));
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

t_error	redirect_prepare(t_ast_redirection *redirection, int *backup_fd)
{
	t_error	err;

	redirect_normalize_fd(redirection);
	err = redirect_expand(redirection);
	if (err.type == ERR_NO)
	{
		err = redirect_check_word(redirection);
		if (err.type == ERR_NO)
			err = redirect_create_backup_fd(redirection->fd, backup_fd);
	}
	return (err);
}
