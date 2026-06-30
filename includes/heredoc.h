#ifndef HEREDOC_H
# define HEREDOC_H

# include "error.h"
# include "libft.h"
# include "token.h"
# include "context.h"

typedef t_vector	t_heredoc_queue;

typedef enum e_heredoc_mode
{
	HEREDOC_MODE_NORMAL,
	HEREDOC_MODE_TAB_STRIP
}	t_heredoc_mode;

typedef struct s_heredoc_queue_item
{
	size_t			*i;
	t_heredoc_mode	mode;
	t_string		path;
	t_string		delim;
	t_string		input;
	bool			is_tty;
}	t_heredoc_queue_item;

typedef struct s_heredoc
{
	t_error			err;
	t_heredoc_queue	queue;
	bool			is_tty;
	int				file_id;
}	t_heredoc;

void	heredoc_init(t_heredoc *state);
void	heredoc_free(t_heredoc *state);
t_error	heredoc_load(t_heredoc *state);

// ============= API FUNCTIONS ================

t_error	heredoc_save_body_in_file(const t_string *path, t_string *content);
t_error	heredoc_read_queue_heredoc_bodies(t_string *input, size_t *start);
t_error	heredoc_track_body_context(t_string *body, t_context_stack *stack);
t_error	heredoc_register(t_string *path ,t_token *delim, t_heredoc_mode mode);
t_error	heredoc_expand(t_string *path);

#endif
