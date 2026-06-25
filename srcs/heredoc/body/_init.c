#include <stdlib.h>
#include "heredoc_body_.h"

void	heredoc_body_init(t_heredoc_body *state)
{
	*(state) = (t_heredoc_body){0};
	buff_init(&state->content, 0, NULL, 0);
}

void	heredoc_body_free(t_heredoc_body *state)
{
	buff_free(&state->content);
	if (state->line != NULL)
		free(state->line);
	*(state) = (t_heredoc_body){0};
}

void	heredoc_body_load(t_heredoc_body *state, t_heredoc_queue_item *item)
{
	state->item = item;
}
