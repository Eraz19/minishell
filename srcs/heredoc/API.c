#include <stdlib.h>
#include "fcntl.h"
#include "shell.h"
#include "heredoc.h"
#include "heredoc_.h"
#include "posix_helpers.h"
#include "heredoc_body_.h"
#include "heredoc_queue_.h"

t_error	heredoc_register(t_string *path, t_token *delim, t_heredoc_mode mode)
{
	t_heredoc_queue_item	item;
	t_heredoc				*state;

	state = shell_get_heredoc();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (create_heredoc_file(state, path).type)
		return (state->err);
	item.is_tty = state->is_tty;
	if (!string_init(&item.path, 0, path->data, (long)path->len))
		return (state->err = error_sys(), string_free(path), state->err);
	if (!string_init(&item.delim, 0, delim->value.data, (long)delim->value.len))
	{
		state->err = error_sys();
		return (string_free(path), string_free(&item.path), state->err);
	}
	if (format_heredoc_delimiter(state, &item.delim).type)
		return (string_free(path), heredoc_queue_item_free(&item), state->err);
	item.mode = mode;
	state->err = heredoc_queue_push(&state->queue, item);
	if (state->err.type)
		return (string_free(path), heredoc_queue_item_free(&item), state->err);
	return (state->err);
}

t_error	heredoc_read_queue_heredoc_bodies(t_string *input, size_t *start)
{
	t_heredoc	*state;

	state = shell_get_heredoc();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	while (state->queue.len != 0)
	{
		if (heredoc_read_queue_heredoc_body(state, input, start).type)
			return (state->err);
	}
	return (state->err);
}

t_error	heredoc_save_body_in_file(const t_string *path, t_string *content)
{
	int		fd;
	t_error	err;
	int		o_flags;

	o_flags = O_WRONLY | O_CREAT | O_TRUNC;
	err = posix_open_with_mode(path->data, o_flags, 0600, &fd);
	if (err.type)
		return (err);
	err = posix_write(fd, content->data, content->len);
	return (posix_close(fd), err);
}

t_error	heredoc_expand(const t_string *heredoc_file_path)
{
	t_error			err;
	t_expander_args	args;
	t_context_stack contexts;
	t_expansion		expansion;
	t_string		heredoc_body;

	err = read_heredoc_body(heredoc_file_path, &heredoc_body);
	if (err.type)
		return (err);
	args.value = heredoc_body;
	context_stack_init(&contexts);
	err = heredoc_track_body_context(&heredoc_body, &contexts);
	if (err.type)
		return (string_free(&heredoc_body), err);
	args.assignment_offset = -1;
	args.role = EXPANDER_HEREDOC_BODY;
	args.contexts = &contexts;
	err = expander_expand(&expansion, &args);
	if (err.type)
		return (context_stack_free(&contexts), string_free(&heredoc_body), err);
	err = store_expansion_result_in_heredoc_file(heredoc_file_path, &expansion);
	context_stack_free(&contexts);
	return (expansion_free(&expansion), string_free(&heredoc_body), err);
}
