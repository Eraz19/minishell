#ifndef HEREDOC__H
# define HEREDOC__H

# include "error.h"
# include "heredoc.h"

# define HEREDOC_TMP_PATH "/tmp/minishell_heredoc_"

// ============= FILE FUNCTIONS ================

t_error	create_heredoc_file(t_heredoc *heredoc, t_string *path);

// ============= EXPANSION FUNCTIONS ================

uint	generate_heredoc_body_expand_flags(void);
t_error	expand_delim(t_heredoc *heredoc, t_string *out, const t_token *delim);

#endif
