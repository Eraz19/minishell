#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "heredoc_.h"
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

static t_error	heredoc_build_path(t_heredoc *state, t_buff *path)
{
	int		i;
	char	*id;
	
	i = 0;
	while (i < INT_MAX)
	{
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
			return (state->err = error_sys(), free(path_str), state->err);
		if (fd == -1)
			free(path_str);
		state->file_id++;
	}
	return (close(fd), state->err);
}
