#ifndef HEREDOC_BODY__H
# define HEREDOC_BODY__H

# include "lexer.h"
# include "heredoc.h"
# include "context.h"

typedef struct s_heredoc_body
{
	size_t					i;
	t_error					err;
	t_heredoc_queue_item	*item;
	t_string				line;
	t_string				content;
	t_context_stack			contexts;
}	t_heredoc_body;

void					heredoc_body_init(t_heredoc_body *state);
void					heredoc_body_free(t_heredoc_body *state);
void					heredoc_body_load(
							t_heredoc_body *state,
							t_heredoc_queue_item *item);

// ============= MAIN FUNCTIONS ================

t_lexer_context_args	heredoc_body_context_rules(void);
t_error					read_heredoc_body_from_input(
							t_heredoc *state,
							t_heredoc_queue_item *item);

// ============= UTILS FUNCTIONS ================

t_error					heredoc_body_escape(t_lexer *state);
bool					is_line_delimiter(t_heredoc_body *state);
t_error					heredoc_body_unescape(t_lexer *state, void *unused);
t_error					get_heredoc_body_line(
							t_heredoc_body *state,
							char *match_EOL,
							size_t *i);

#endif
