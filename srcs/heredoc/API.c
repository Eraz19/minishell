#include <stdlib.h>
#include "shell.h"
#include "heredoc.h"
#include "heredoc_.h"
#include "heredoc_body_.h"
#include "heredoc_queue_.h"

static t_error	heredoc_store_body(t_heredoc *state, char *input, size_t *start)
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

}
