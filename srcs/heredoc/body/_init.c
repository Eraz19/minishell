#include "heredoc_body_.h"

void	heredoc_body_init(t_heredoc_body *state)
{
	*(state) = (t_heredoc_body){0};
	context_stack_init(&state->contexts);
	string_init(&state->content, 0, NULL, 0);
}

void	heredoc_body_free(t_heredoc_body *state)
{
	string_free(&state->content);
	string_free(&state->line);
	context_stack_free(&state->contexts);
	*(state) = (t_heredoc_body){0};
}

void	heredoc_body_load(t_heredoc_body *state, t_heredoc_queue_item *item)
{
	state->i = *item->i;
	state->item = item;
}
