#include <stdlib.h>
#include "fcntl.h"
#include "shell.h"
#include "heredoc.h"
#include "heredoc_.h"
#include "posix_helpers.h"
#include "heredoc_body_.h"
#include "heredoc_queue_.h"

t_error	heredoc_body_save_content(char *path, t_buff *content)
{
	int		fd;
	t_error	err;

	err = posix_open_with_mode(
			path, O_WRONLY | O_CREAT | O_TRUNC, 0600, &fd);
	if (err.type)
		return (err);
	err = posix_write(fd, content->data, content->len);
	if (err.type)
		return (posix_close(fd), err);
	return (posix_close(fd), err);
}

t_error	heredoc_store_all(char *input, size_t *start)
{
	t_heredoc	*state;

	state = shell_get_heredoc();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	while (state->queue.len != 0)
	{
		if (heredoc_store_body(state, input, start).type)
			return (state->err);
	}
	return (state->err);
}

t_error	heredoc_add_to_queue(
	t_buff *path,
	char *delim,
	t_heredoc_mode mode,
	bool is_tty)
{
	t_heredoc_queue_item	item;
	t_heredoc				*state;

	state = shell_get_heredoc();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (heredoc_create_file(state, path).type)
		return (state->err);
	item.is_tty = is_tty;
	item.path = buff_get_string(path);
	if (item.path == NULL)
		return (state->err = error_sys(), buff_free(path), state->err);
	item.delim = str_dup(delim);
	if (item.delim == NULL)
	{
		state->err = error_sys();
		return (buff_free(path), free(item.path), state->err);
	}
	if (heredoc_build_delimiter(state, &item.delim).type)
		return (buff_free(path), heredoc_queue_item_free(&item), state->err);
	item.mode = mode;
	state->err = heredoc_queue_push(&state->queue, item);
	if (state->err.type)
		return (buff_free(path), heredoc_queue_item_free(&item), state->err);
	return (state->err);
}

bool	heredoc_is_delim_quoted(t_buff *delim)
{
	if (buff_get_index(delim, '\'') != -1)
		return (true);
	else if (buff_get_index(delim, '"') != -1)
		return (true);
	else if (buff_get_index(delim, '\\') != -1)
		return (true);
	return (false);
}

t_error	heredoc_track_body_context(t_buff *body, t_context_stack *stack)
{
	t_error	err;
	t_lexer	lexer;
	char	*input;

	input = buff_get_string(body);
	if (input == NULL)
		return (error_sys());
	lexer_init(&lexer);
	err = lexer_push_input(&lexer, input);
	if (!err.type)
		err = lexer_track_context(&lexer, stack, heredoc_body_context_rules());
	return (lexer_free(&lexer), err);
}
