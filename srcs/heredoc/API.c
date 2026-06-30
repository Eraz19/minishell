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

t_error	heredoc_track_body_context(t_string *body, t_context_stack *stack)
{
	t_error					err;
	t_lexer					lexer;
	t_context_stack_item	*body_ctx;

	err = context_stack_item_init(&body_ctx, CONTEXT_HEREDOC);
	if (err.type)
		return (err);
	body_ctx->start = 0;
	body_ctx->end = body->len;
	err = context_stack_push(stack, body_ctx);
	if (err.type)
		return (free(body_ctx), err);
	lexer_init(&lexer);
	err = lexer_push_input(&lexer, body);
	if (!err.type)
		err = lexer_track_context(&lexer, stack, heredoc_body_context_rules());
	return (lexer_free(&lexer), err);
}
