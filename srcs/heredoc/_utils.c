#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "heredoc_.h"
#include "posix_helpers.h"
#include "posix_helpers.h"
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

static inline t_error	heredoc_handle_error(t_heredoc *state, t_string *path)
{
	string_free(path);
	if (state->err.type == ERR_NO
		|| (state->err.type == ERR_LIBC
			&& state->err.saved_errno == EEXIST
			&& state->file_id == INT_MAX))
		state->err = error(ERR_HEREDOC_MAX_ID_REACHED);
	error_print(state->err, "heredoc", "unable to create tmp file", NULL, NULL);
	return (state->err);
}

t_error	heredoc_create_file(t_heredoc *state, t_string *path)
{
	int		fd;
	int		oflag;
	size_t	initial_len;

	oflag = O_CREAT | O_EXCL | O_WRONLY;
	if (!string_init(path, 0, HEREDOC_TMP_PATH, sizeof(HEREDOC_TMP_PATH) - 1))
		return (state->err = error_sys());
	initial_len = path->len;
	fd = -1;
	while (state->file_id < INT_MAX)
	{
		state->file_id++;
		if (!string_append_format(path, "%i", (int)state->file_id))
			return (state->err = error_sys(), string_free(path), state->err);
		state->err = posix_open_with_mode(path->data, oflag, 0600, &fd);
		if (state->err.type == ERR_NO)
			return (close(fd), state->err);
		else if (state->err.type != ERR_LIBC
			|| state->err.saved_errno != EEXIST)
			break ;
		path->len = initial_len;
	}
	return (heredoc_handle_error(state, path));
}
