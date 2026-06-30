#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <asm-generic/errno-base.h>
#include "libft.h"
#include "heredoc_.h"
#include "heredoc_body_.h"
#include "posix_helpers.h"
#include "heredoc_queue_.h"
//#include "expander.h"

static inline bool	max_id_reached(t_error err, int file_id)
{
	int	errno;

	errno = err.saved_errno;
	return (err.type == ERR_LIBC && errno == EEXIST && file_id == INT_MAX);
}

t_error	create_heredoc_file(t_heredoc *state, t_string *path)
{
	int		fd;
	int		o_flag;
	size_t	initial_len;

	o_flag = O_CREAT | O_EXCL | O_WRONLY;
	if (!string_init(path, 0, HEREDOC_TMP_PATH, sizeof(HEREDOC_TMP_PATH) - 1))
		return (state->err = error_sys());
	fd = -1;
	initial_len = path->len;
	while (state->file_id < INT_MAX)
	{
		state->file_id++;
		if (!string_append_format(path, "%i", (int)state->file_id))
			return (state->err = error_sys(), string_free(path), state->err);
		state->err = posix_open_with_mode(path->data, o_flag, 0600, &fd);
		if (state->err.type == ERR_NO)
			return (close(fd), state->err);
		if (state->err.type != ERR_LIBC || state->err.saved_errno != EEXIST)
			break ;
		path->len = initial_len;
	}
	if (state->err.type == ERR_NO || max_id_reached(state->err, state->file_id))
		state->err = error(ERR_HEREDOC_MAX_ID_REACHED);
	error_print(state->err, "heredoc", "unable to create tmp file", NULL, NULL);
	return (string_free(path), state->err);
}

t_error	heredoc_read_queue_heredoc_body(
			t_heredoc *state,
			t_string *input,
			size_t *start)
{
	size_t					i;
	t_heredoc_queue_item   	item;

	i = 0;
	state->err = heredoc_queue_pop(&state->queue, &item);
	if (state->err.type)
		return (state->err);
	if (input == NULL)
	{
		if (!string_init(&item.input, 1, "", -1))
			return (state->err = error_sys());
	}
	else
		if (!string_init(&item.input, 0, input->data, (long)input->len))
			return (state->err = error_sys());
	if (start == NULL || *start > item.input.len)
		item.i = &i;
	else 
		item.i = start;
	if (read_heredoc_body_from_input(state, &item).type)
		return (heredoc_queue_item_free(&item), state->err);
	return (heredoc_queue_item_free(&item), state->err);
}

t_error	format_heredoc_delimiter(t_heredoc *state, t_string *delim)
{
	//t_expander_args	args;
	//char			**delim_exp;

	//args.value = delim_buff;
	//args.role = EXPANDER_HEREDOC_DELIMITER;
	//args.contexts = NULL;
	//state->err = expander_expand_word(&delim_exp, &args);
	//if (state->err.type || delim_exp == NULL)
	//	return (buff_free(&delim_buff), free(*delim), state->err);
	//buff_free(&delim_buff);
	//if (delim_exp[0] == NULL)
	//	return (free(*delim), str_array_free(&delim_exp), state->err);
	if (!string_append_n(delim, "\n", 1))
		return (state->err = error_sys());
	return (state->err);
}
