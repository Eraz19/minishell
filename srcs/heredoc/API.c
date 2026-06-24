#include <stdlib.h>
#include "shell.h"
#include "heredoc_.h"
#include "heredoc_body_.h"
#include "heredoc_queue_.h"

#include <stdio.h> //DEBUG
t_error	heredoc_store_all(char *input, size_t *start)
{
	t_heredoc_queue_item	item;
	t_heredoc				*state;

	state = shell_get_heredoc();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	while (state->queue.len != 0)
	{
		state->err = heredoc_queue_pop(&state->queue, &item);
		if (state->err.type)
			return (state->err);
		item.i = start;
		item.input = input;
		if (heredoc_body_store(state, &item).type)
			return (state->err);
	}
	return (state->err);
}

#include <stdio.h> //DEBUG
t_error	heredoc_add_to_queue(t_buff *path, char *delim, t_heredoc_mode mode)
{
	t_heredoc_queue_item	item;
	t_heredoc				*state;

	printf("=====> In heredoc_add_to_queue\n");
	state = shell_get_heredoc();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	printf("=====> Heredoc state obtained\n");
	if (heredoc_create_file(state, path).type)
		return (state->err);
	printf("=====> Heredoc file created with path: %s\n", buff_get_string(path));
	item.path = buff_get_string(path);
	if (item.path == NULL)
		return (buff_free(path), state->err = error_sys());
	printf("=====> Heredoc path set to: %s\n", item.path);
	item.delim = str_dup(delim);
	if (item.delim == NULL)
		return (buff_free(path), free(item.path), state->err = error_sys());
	if (heredoc_build_delimiter(state, &item.delim).type)
		return (buff_free(path), heredoc_queue_item_free(&item), state->err);
	printf("=====> Heredoc delimiter set to: %s\n", item.delim);
	item.mode = mode;
	printf("=====> Heredoc mode set to: %i\n", (int)item.mode);
	printf("=====> Pushing heredoc item to queue\n");
	state->err = heredoc_queue_push(&state->queue, item);
	if (state->err.type)
		return (buff_free(path), heredoc_queue_item_free(&item), state->err);
	printf("=====> Heredoc item pushed to queue\n");
	return (state->err);
}
