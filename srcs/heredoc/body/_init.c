#include <stdlib.h>
#include "heredoc_body_.h"
#include "heredoc_queue_.h"

void	heredoc_body_init(t_heredoc_body *state)
{
	*(state) = (t_heredoc_body){0};
	buff_init(&state->content, 0, NULL, 0);
}

void	heredoc_body_free(t_heredoc_body *state)
{
	buff_free(&state->content);
	heredoc_queue_item_free(state->item);
	if (state->input != NULL)
		free(state->input);
	if (state->line != NULL)
		free(state->line);
	*(state) = (t_heredoc_body){0};
}

t_error	heredoc_body_load(
	t_heredoc_body *state,
	t_heredoc_queue_item *item,
	bool is_stdin)
{
	state->i = item->i;
	state->item = item;
	state->is_stdin = is_stdin;
	if (item->input == NULL)
		state->input = str_dup("");
	else
		state->input = str_dup(item->input);
	if (state->input == NULL)
		return (state->err = error_sys());
	return (state->err);
}
