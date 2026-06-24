#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "heredoc_.h"
#include "expander.h"

t_error	heredoc_build_delimiter(t_heredoc *state, char **delim)
{
	char	*delim_;
	t_buff	delim_buff;
	char	**delim_exp;

	if (!buff_init(&delim_buff, 0, *delim, (long)str_len(*delim)))
		return (state->err = error_sys());
	state->err = expander_expand_word(
		&delim_exp,
		delim_buff,
		NULL,
		EXPANDER_HEREDOC_DELIMITER);
	if (state->err.type || delim_exp == NULL)
		return (buff_free(&delim_buff), free(*delim), state->err);
	buff_free(&delim_buff);
	if (delim_exp[0] == NULL)
		return (free(*delim), str_array_free(&delim_exp), state->err);
	delim_ = str_join(delim_exp[0], "\n");
	if (delim_ == NULL)
		state->err = error_sys();
	str_array_free(&delim_exp);
	return (free(*delim), *delim = delim_, state->err);
}

static t_error	heredoc_build_path(t_heredoc *state, t_buff *path)
{
	int		i;
	char	*id;
	
	i = 0;
	while (i < INT_MAX)
	{
		if (!buff_init(path, 0, /*"/tmp/minishell_heredoc_"*/"/home/alexander/Documents/42/common_core/minishell/heredoc_", 59))
			return (state->err = error_sys());
		id = ft_itoa(i);
		if (id == NULL)
			return (buff_free(path), state->err = error_sys());
		if (!buff_append(path, id, (long)str_len(id)))
			return (free(id), buff_free(path), state->err = error_sys());
		if (access(buff_get_string(path), F_OK) == 0)
		{
			free(id);
			buff_free(path);
		}
		else
			return (free(id), state->err);
		++i;
	}
	return (state->err);
}

t_error	heredoc_create_file(t_heredoc *state, t_buff *path)
{
	int		fd;
	char	*path_str;

	fd = -1;
	while (fd == -1)
	{
		if (heredoc_build_path(state, path).type)
			return (state->err);
		path_str = buff_get_string(path);
		fd = open(path_str, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd == -1 && errno != EEXIST)
			return (free(path_str), state->err = error_sys());
		if (fd == -1)
			free(path_str);
		state->file_id++;
	}
	return (close(fd), state->err);
}
