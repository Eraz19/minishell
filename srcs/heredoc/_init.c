#include "heredoc.h"
#include "heredoc_queue_.h"
#include "utils.h"

void	heredoc_init(t_heredoc *state)
{
	*(state) = (t_heredoc){0};
	heredoc_queue_init(&state->queue);
	state->file_id = (size_t)get_now_unix_seconds();
}

void	heredoc_free(t_heredoc *state)
{
	heredoc_queue_free(&state->queue);
	*(state) = (t_heredoc){0};
}

void	heredoc_load(t_heredoc *state, bool is_stdin)
{
	state->is_stdin = is_stdin;
}
