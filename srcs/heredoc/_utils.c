#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "heredoc_.h"
#include "posix_helpers.h"
#include "heredoc_body_.h"
#include "heredoc_queue_.h"
//#include "expander.h"

t_error	heredoc_build_delimiter(t_heredoc *state, char **delim)
{
	//t_expander_args	args;
	char			*delim_;
	t_buff			delim_buff;
	//char			**delim_exp;

	if (!buff_init(&delim_buff, 0, *delim, (long)str_len(*delim)))
		return (state->err = error_sys());
	//args.value = delim_buff;
	//args.role = EXPANDER_HEREDOC_DELIMITER;
	//args.contexts = NULL;
	//state->err = expander_expand_word(&delim_exp, &args);
	//if (state->err.type || delim_exp == NULL)
	//	return (buff_free(&delim_buff), free(*delim), state->err);
	//buff_free(&delim_buff);
	//if (delim_exp[0] == NULL)
	//	return (free(*delim), str_array_free(&delim_exp), state->err);
	delim_ = str_join(/*delim_exp[0]*/*delim, "\n");
	if (delim_ == NULL)
		state->err = error_sys();
	//str_array_free(&delim_exp);
	return (free(*delim), *delim = delim_, state->err);
}

static t_error	heredoc_try_build_path(t_heredoc *state, t_buff *path, int i)
{
	char	*id;
	bool	exists;

	if (!buff_init(path, 0, HEREDOC_TMP_PATH, sizeof(HEREDOC_TMP_PATH) - 1))
		return (state->err = error_sys());
	id = ft_itoa(i);
	if (id == NULL)
		return (state->err = error_sys(), buff_free(path), state->err);
	if (!buff_append(path, id, (long)str_len(id)))
	{
		state->err = error_sys();
		return (free(id), buff_free(path), state->err);
	}
	state->err = posix_access(buff_get_string(path), F_OK, &exists);
	if (state->err.type)
		return (free(id), buff_free(path), state->err);
	if (exists)
		return (free(id), buff_free(path), state->err);
	else
		return (free(id), state->err);
}

static t_error	heredoc_build_path(t_heredoc *state, t_buff *path)
{
	int	i;

	i = 0;
	while (i < INT_MAX)
	{
		state->err = heredoc_try_build_path(state, path, i);
		if (state->err.type)
			return (state->err);
		if (path->data != NULL)
			return (state->err);
		++i;
	}
	return (state->err);
}

t_error	heredoc_create_file(t_heredoc *state, t_buff *path)
{
	int		fd;
	int		flags;
	char	*path_str;

	fd = -1;
	flags = O_CREAT | O_EXCL | O_WRONLY;
	while (fd == -1)
	{
		if (heredoc_build_path(state, path).type)
			return (state->err);
		path_str = buff_get_string(path);
		state->err = posix_open_with_mode(path_str, flags, 0600, &fd);
		if (state->err.type && state->err.saved_errno != EEXIST)
			return (free(path_str), buff_free(path), state->err);
		if (fd == -1)
		{
			free(path_str);
			buff_free(path);
		}
		state->file_id++;
	}
	return (posix_close(fd), state->err);
}

t_error	heredoc_store_body(t_heredoc *state, char *input, size_t *start)
{
	size_t					i;
	t_heredoc_queue_item	item;

	i = 0;
	state->err = heredoc_queue_pop(&state->queue, &item);
	if (state->err.type)
		return (state->err);
	if (input == NULL)
		item.input = str_dup("");
	else
		item.input = str_dup(input);
	if (start == NULL || *start > str_len(item.input))
		item.i = &i;
	else 
		item.i = start;
	if (heredoc_body_read(state, &item).type)
		return (heredoc_queue_item_free(&item), state->err);
	return (heredoc_queue_item_free(&item), state->err);
}
