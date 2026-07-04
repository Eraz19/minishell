#ifndef HEREDOC_H
# define HEREDOC_H

# include "error.h"
# include "libft.h"
# include "token.h"

typedef t_vector	t_heredoc_queue;

typedef enum e_here_mode
{
	HEREDOC_MODE_NORMAL,
	HEREDOC_MODE_TAB_STRIP
}	t_here_mode;

typedef struct s_heredoc_item
{
	size_t		*i;
	t_here_mode	mode;
	t_string	path;
	t_string	delim;
	t_string	input;
	bool		is_tty;
}	t_heredoc_item;

typedef struct s_heredoc
{
	t_error			err;
	t_heredoc_queue	queue;
	bool			is_tty;
	int				file_id;
}	t_heredoc;

void	heredoc_init(t_heredoc *heredoc);
void	heredoc_free(t_heredoc *heredoc);
t_error	heredoc_load(t_heredoc *heredoc);

// ============= API FUNCTIONS ================

t_error	heredoc_expand_body(const t_string *path);
t_error	heredoc_read_body_from_input(const t_string *input, size_t *start);
t_error	heredoc_get_body_contexts(t_context_stack *out, const t_string *body);
t_error	heredoc_register(t_string *out, const t_token *delim, t_here_mode mode);

#endif
