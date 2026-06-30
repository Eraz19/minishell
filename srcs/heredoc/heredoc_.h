#ifndef HEREDOC__H
# define HEREDOC__H

# include "error.h"
# include "heredoc.h"

# define HEREDOC_TMP_PATH "/tmp/minishell_heredoc_"

// ============= UTILS FUNCTIONS ================

t_error	create_heredoc_file(t_heredoc *state, t_string *path);
t_error	format_heredoc_delimiter(t_heredoc *state, t_string *delim);
t_error	heredoc_read_queue_heredoc_body(
			t_heredoc *state,
			t_string *input,
			size_t *start);

#endif
