#include <stdlib.h>
#include "fcntl.h"
#include "shell.h"
#include "heredoc.h"
#include "heredoc_.h"
#include "posix_helpers.h"
#include "heredoc_body_.h"
#include "heredoc_queue_.h"

t_error	heredoc_body_save_content(t_string *path, t_string *content)
{
	int		fd;
	t_error	err;

	err = posix_open_with_mode(
			path->data, O_WRONLY | O_CREAT | O_TRUNC, 0600, &fd);
	if (err.type)
		return (err);
	err = posix_write(fd, content->data, content->len);
	if (err.type)
		return (posix_close(fd), err);
	return (posix_close(fd), err);
}

t_error	heredoc_store_all(t_string *input, size_t *start)
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
			t_string *path,
			t_token *delim,
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
	if (!string_init(&item.path, 0, path->data, (long)path->len))
		return (state->err = error_sys(), string_free(path), state->err);
	if (!string_init(&item.delim, 0, delim->value.data, (long)delim->value.len))
		return (state->err = error_sys(), string_free(path),
			string_free(&item.path), state->err);
	if (heredoc_build_delimiter(state, &item.delim).type)
		return (string_free(path), heredoc_queue_item_free(&item), state->err);
	item.mode = mode;
	state->err = heredoc_queue_push(&state->queue, item);
	if (state->err.type)
		return (string_free(path),
			heredoc_queue_item_free(&item), state->err);
	return (state->err);
}

bool	heredoc_is_delim_quoted(t_string *delim)
{
	if (string_get_index_c(delim, '\'') != -1)
		return (true);
	else if (string_get_index_c(delim, '"') != -1)
		return (true);
	else if (string_get_index_c(delim, '\\') != -1)
		return (true);
	return (false);
}

t_error	heredoc_track_body_context(t_string *body, t_context_stack *stack)
{
	t_error	err;
	t_lexer	lexer;

	lexer_init(&lexer);
	err = lexer_push_input(&lexer, body);
	if (!err.type)
		err = lexer_track_context(&lexer, stack, heredoc_body_context_rules());
	return (lexer_free(&lexer), err);
}
