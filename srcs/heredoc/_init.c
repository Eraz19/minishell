#include "heredoc.h"
#include "heredoc_.h"
#include "input_mode.h"
#include "heredoc_queue_.h"
#include <unistd.h>
#include <errno.h>

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
	t_input_mode	mode;

	state->err = input_mode_set(&mode);
	if (state->err.type != ERR_NO)
		return (state->err = heredoc_error_qualify(state->err));
	return (state->is_tty = mode == INPUT_MODE_STDIN_TTY, state->err);
}

# include <stdio.h>
# include "logs.h"
# include <string.h>
void	heredoc_unlink(const char *heredoc_path)
{
	bool	succeed;
	int		saved_errno;

	succeed = unlink(heredoc_path) == 0;
	if (succeed == true)
		fprintf(stderr, "%s[%s()] heredoc unlinked: '%s%s%s'%s\n",
			YELLOW, __func__, BLUE, heredoc_path, YELLOW, NC);
	else
	{
		saved_errno = errno;
		fprintf(stderr, "%s[%s()] heredoc unlink FAILED: '%s%s%s'%s (%s)\n",
			RED, __func__, BLUE, heredoc_path, RED, strerror(saved_errno), NC);
	}
}
