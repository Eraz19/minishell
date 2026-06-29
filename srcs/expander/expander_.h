#ifndef EXPANDER__H
# define EXPANDER__H

# include "expander_field_.h"

typedef enum e_expander_role
{
	EXPANDER_NORMAL,
	EXPANDER_ASSIGNMENT,
	EXPANDER_REDIRECT_FILENAME,
	EXPANDER_HEREDOC_DELIMITER,
	EXPANDER_HEREDOC_BODY
}	t_expander_role;

typedef	struct s_expander_args
{
	t_buff			value;
	t_expander_role role;
	t_context_stack *contexts;
	ssize_t			assignment_offset;
}	t_expander_args;

typedef struct s_expander
{
	t_error				err;
	t_expander_role		role;
	t_expander_word		word;
	t_expander_fields	fields;
	t_expander_word		word_exp;
	t_expander_fields	fields_exp;
	ssize_t				assignement_offset;
}	t_expander;

void	expander_free(t_expander *state);
void	expander_init(t_expander *state, t_expander_role role);
t_error	expander_load(t_expander *state, t_expander_args *args);

t_error	expander_expand(char ***expansion, t_expander_args *args);
t_error	read_heredoc_body(t_buff *heredoc_file_path, t_buff *heredoc_body);

#endif
