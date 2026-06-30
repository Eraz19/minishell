#include "utils.h"
#include "heredoc.h"
#include "heredoc_queue_.h"

void	heredoc_init(t_heredoc *state)
{
	*(state) = (t_heredoc){0};
	heredoc_queue_init(&state->queue);
	state->file_id = -1;
}

void	heredoc_free(t_heredoc *state)
{
	heredoc_queue_free(&state->queue);
	*(state) = (t_heredoc){0};
}

t_error	heredoc_load(t_heredoc *state)
{
	t_scanner_mode	mode;

	state->err = scan_set_mode(&mode);
	if (state->err.type != ERR_NO)
		return (state->err);
	return (state->is_tty = mode == SCAN_STDIN_TTY, state->err);
}
